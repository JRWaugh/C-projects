#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define LEN 25
#define NIBBLE 255
#define ROW_LEN 16
#define COL_HEADER "Offset    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F   Press Enter to print next line.\n"
#define MENU "1. Enter offset\n2. Edit byte at specified row and column\n3. Print all data\n4. Quit program\n"
typedef struct {
    unsigned char *data;
    char filename[LEN];
    unsigned int size;
    char p_filename[LEN];
    unsigned int cursor;
} log_t;

//FILE *open_file(struct log_t log);
void get_file_info(FILE *fp, log_t *log);
void print_data_row(log_t *log);
void edit_data(log_t *log, unsigned int address, unsigned int value);
int create_data_edit(log_t *log);
int read_number(char *mode);

int main()
{
    FILE *fp;
    log_t log;
    int selection = -1, i = 0;
    char c, buffer[LEN];

    do {
        printf("--HEX EDITOR--\nEnter name of file to read (or type exit to quit): ");
        fgets(log.filename, LEN, stdin);
        if (log.filename[strlen(log.filename) - 1] == '\n')
            log.filename[strlen(log.filename) - 1] = '\0';
        
        fp = fopen(log.filename, "rb");
        if(!fp)
            printf("Invalid filename.");
    } while(!fp);

    get_file_info(fp, &log);
    fclose(fp);
    if(fp = fopen(log.p_filename, "r")) {
        do {
            printf("Patch file found. Apply changes in patch file (y/n): ");
            if((c = getchar()) == 'y') {
                unsigned int address, value; 
                while(fgets(buffer, LEN, fp))
                    if(sscanf(buffer, "%x %x", &address, &value) == 2)
                    //Ideally should verify that the addresses aren't out of range. Do it in the func.
                        edit_data(&log, address, value);
                printf("Patch applied.\n");
            } else if ( c != 'n')
                printf("Invalid input.\n");
            while (getchar() != '\n'){}; //clear buffer in case of strange input
        } while (c != 'y' && c != 'n');
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
                //Set cursor position
                do {
                    printf("Enter offset between 0x0 - %#x (format: '02' or '0x02'): ", log.size - 1);
                    log.cursor = read_number("%x");
                    if ( log.cursor < 0  ||  (log.cursor > log.size - 1) )
                        printf("Invalid input.\n");
                } while ( log.cursor < 0  ||  (log.cursor > log.size - 1) );
                log.cursor -= log.cursor % 16; //Round down cursor to a multiple of 16 to find the desired row 
                
                printf(COL_HEADER);
                while (log.cursor < log.size && c != 'q') {
                    c = 0;
                    print_data_row(&log);                 
                    if (log.cursor < log.size) { // More data to print
                        printf("  --More--  ");
                        c = getchar();
                        if(c != '\n') //If input was given, consume everything in the buffer after the first character
                            while (getchar() != '\n'){}
                    } else { // No more data to print
                        printf("  EOF\n");
                    }
                    
                    switch (c) {
                        case 'e': 
                            create_data_edit(&log);
                            break;
                        case 'q':
                            printf("Quit blah.\n");
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
                printf(COL_HEADER);
                log.cursor = 0;
                while(log.cursor < log.size){
                    print_data_row(&log);
                    printf("\n");
                }
            
            case 4:
                //Close program
                printf("Closing program.\n");

        }
    } while (selection != 4);
    return 0;
}

void get_file_info(FILE *fp, log_t *log)
{
    strcpy(log->p_filename, log->filename);
    strcat(log->p_filename, ".patch");
    fseek(fp, 0, SEEK_END);
    log->size = ftell(fp);
    rewind(fp);
    log->data = malloc(log->size + 1);
    fread(log->data, sizeof(char), log->size, fp);
    log->cursor = 0;    
}

void print_data_row(log_t *log) {
    //Prints a row of data and moves cursor to the next row
    unsigned int i = 0;
    printf("%08x  ", log->cursor);
    for (i = log->cursor; i < log->cursor + ROW_LEN; i++) {
        if(i < log->size)
            printf("%02x ", log->data[i]);
        else
            printf("%2c ", ' ');
    }
    printf("  ");
    for (i = log->cursor; i < log->cursor + ROW_LEN; i++) {
        if (isprint(log->data[i]) && i < log->size)
            printf("%c", log->data[i]);
        else
            printf("%c", '.');          
    }

    log->cursor += ROW_LEN;
}

void edit_data(log_t *log, unsigned int address, unsigned int value) {
    printf("%x %x", address, value);
    log->data[address] = (unsigned char)value;
}

int create_data_edit(log_t *log) {
    unsigned int address, input;
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

    FILE *fp = fopen(log->p_filename, "a");
    if (fp) {
        fprintf(fp, "%x %x\n", address, input);
        fclose(fp);
        edit_data(log, address, input);
        return 1;
    } else {
        return 0;
    }
}

int read_number(char *mode){
    int number = -1;
    char input[LEN];
    fgets(input, LEN, stdin);
    sscanf(input, mode, &number);
    return number;
}