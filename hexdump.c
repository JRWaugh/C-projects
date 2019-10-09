#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define LEN 25
#define NIBBLE 255
#define ROW_LEN 16
#define COL_HEADER "Offset    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F"
#define MENU "1. Enter offset\n2. Edit byte at specified row and column\n3. Print all data\n4. Quit program\n"
typedef struct {
    unsigned char *data;
    char filename[LEN];
    unsigned int size;
    char p_filename[LEN];
    unsigned int cursor;
} log_t;

void get_file_info(FILE *fp, log_t *log);
int print_data_row(log_t *log);
void edit_data(log_t *log, unsigned int address, unsigned int value);
void create_data_edit(log_t *log);
int read_number(char *mode);

int main()
{
    FILE *fp;
    log_t log;
    int selection = -1;
    unsigned int address, value;
    char c, trash_ch, buffer[LEN];

    //Ask user for filename until a file is successfully found
    do {
        printf("--HEX EDITOR--\nEnter filename (or type quit to quit): ");
        fgets(log.filename, LEN, stdin);
        if (log.filename[strlen(log.filename) - 1] == '\n')
            log.filename[strlen(log.filename) - 1] = '\0';
        
        if(!strcmp(log.filename, "quit")){
            printf("Ending program.\n");
            return 1;
        }
        
        if(!(fp = fopen(log.filename, "rb")))
            printf("Invalid filename.");
    } while(!fp);
    get_file_info(fp, &log);
    fclose(fp);

    //Check if opening patch file returns a non-NULL file pointer
    if(fp = fopen(log.p_filename, "r")) {
        do {
            printf("Patch file found. Apply changes in patch file (y/n): ");
            if( (c = getchar())  ==  'y' ) { 
                while(fgets(buffer, LEN, fp))
                    if(sscanf(buffer, "%x %x", &address, &value) == 2)
                        edit_data(&log, address, value); //Ideally should verify that the addresses aren't out of range. Do it in the func.
                printf("Patch applied.\n");
            } else if ( c != 'n')
                printf("Invalid input.\n");
            while ( (trash_ch = getchar()) != '\n'  &&  trash_ch != EOF ); //clear buffer in case of strange input
        } while (c != 'y' && c != 'n');
        fclose(fp);
    }
    
    //Start the main loop of the program
    do {
        //Print menu and ask user for sleection
        printf("Filename: \"%s\" / File Size: %d Bytes\n%s", log.filename, log.size, MENU);
        do {
            //1. Enter offset 2. Edit byte at specified row and column 3. Undo changes 4. Print all data 5. Quit and save changes
            printf("Selection: ");
            selection = read_number("%d");
            if(selection < 1 || selection > 5)
                printf("Invalid input.\n");
        } while (selection < 1 || selection > 5);

        switch (selection) {
            case 1:
                do {
                    printf("Enter offset between 0x0 - %#x (format: '02' or '0x02'): ", log.size - 1);
                    log.cursor = read_number("%x");
                    if ( log.cursor < 0  ||  (log.cursor > log.size - 1) )
                        printf("Invalid input.\n");
                } while ( log.cursor < 0  ||  (log.cursor > log.size - 1) );

                //Round down cursor to a multiple of 16 to find the desired row 
                log.cursor -= log.cursor % 16;
                
                printf("%s%20c%s\n", COL_HEADER, ' ', "e: edit/q: quit/any: cont.");
                //Print rows one at a time, waiting for user input after each print
                while (c != 'q' && print_data_row(&log)) {         
                    c = getchar();
                    if(c != '\n')
                        while ((trash_ch = getchar()) != '\n' && trash_ch != EOF);

                    switch (tolower(c)) {
                        case 'e': 
                            create_data_edit(&log);
                            break;
                        case 'q':
                            printf("Ending print.\n");
                            break;
                        default:
                            break;
                    }
                }
                break;

            case 2:
                //Edit data at specified address
                create_data_edit(&log);
                break;

            case 3:
                //Print all data
                printf("%s\n", COL_HEADER);
                log.cursor = 0;
                while(print_data_row(&log)) 
                    printf("\n");
                break;
            
            case 4:
                //Close program
                printf("Closing program.\n");
                break;

        }
    } while (selection != 4);
    free(log.data);
    return 0;
}

void get_file_info(FILE *fp, log_t *log)
{
    //Function extracts all useful information from file and places it in a log structure
    strcpy(log->p_filename, log->filename);
    strcat(log->p_filename, ".patch");
    fseek(fp, 0, SEEK_END);
    log->size = ftell(fp);
    rewind(fp);
    log->data = malloc(log->size + 1);
    fread(log->data, sizeof(char), log->size, fp);
    log->cursor = 0;    
}

int print_data_row(log_t *log) {
    //Prints a row of data and moves cursor to the next row
    unsigned char hex_to_string[ROW_LEN + 1] = {0};
    printf("%08x  ", log->cursor);
    for (int i = 0; i < ROW_LEN; i++, log->cursor++) {
        //Print each byte one by one
        if( log->cursor  <  log->size )
            printf("%02x ", log->data[log->cursor]);
        else
            printf("%2c ", ' ');
        
        //Create a string of the bytes being iterated over
        if ( isprint(log->data[log->cursor])  &&  log->cursor < log->size )
            hex_to_string[i] = log->data[log->cursor];
        else 
            hex_to_string[i] = '.';      
    }
    printf(" %s  ", hex_to_string);

    if(log->cursor < log->size)
        return 1;
    else {
        printf("  End of data.\n");
        return 0;  
    }
}

void edit_data(log_t *log, unsigned int address, unsigned int value) {
    log->data[address] = (unsigned char)value;
}

void create_data_edit(log_t *log) {
    unsigned int address, input;
    FILE *fp;
    do {
        printf("Enter hex address to edit: ");
        address = read_number("%x");
        if(address < 0 || address > log->size) 
            printf("Invalid input.\n");
    } while (address < 0 || address > log->size);

    do {
        printf("Modifying address %#x (current value: %x): ", address, log->data[address]);
        input = read_number("%x");
        if(input < 0 || input > NIBBLE)
            printf("Invalid input.\n");
    } while (input < 0 || input > NIBBLE);

     
    if (fp = fopen(log->p_filename, "a")) {
        fprintf(fp, "%x %x\n", address, input);
        fclose(fp);
        edit_data(log, address, input);
        printf("Changes written to patch file '%s'.\n", log->p_filename);
    } else {
        printf("Error writing changes to patch file.\n");
    }
}

int read_number(char *mode){
    int number = -1;
    char input[LEN];
    fgets(input, LEN, stdin);
    sscanf(input, mode, &number);
    return number;
}