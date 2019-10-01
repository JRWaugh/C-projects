#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define LEN 100
#define ROW_LEN 16
#define COL_HEADER "          00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F   Press Enter to print next line.\n"
struct log_t
{
    char *data;
    char filename[LEN];
    int size;
    char n_filename[LEN];
};

//FILE *open_file(struct log_t log);
void get_file_info(struct log_t *log, char *filename);
int print_data_row(int start, char *data, size_t size);
void edit_data(struct log_t *log, int row, int column, int value);
int read_number();
int read_hex_number(const char *prompt_text);
int menu_selection();

int main(int argc, char **argv)
{
    struct log_t log;
    int selection = -1, i = 0;
    char c = '\n';

    if (argc == 1)
        get_file_info(&log, "\0");
    else if (argc == 2)
        get_file_info(&log, argv[1]);
    else if (argc > 2)
        printf("Too many args!");

    printf("--HEX EDITOR--\nFilename: \"%s\" / File Size: %d Bytes\n", log.filename, log.size);
    selection = menu_selection(); 
    // Menu options:  1. Enter offset, 2. Edit specific byte, 3. Undo changes, 4. Print all data, 5. Quit and save changes
    switch (selection) {
        case 1:
            printf("Enter offset (0x0 - %#x). Input format '02' or '0x02':\n", log.size);
            int offset = read_hex_number("Offset: ");
            //Round down offset to a multiple of 16 to find the desired row 
            offset -= offset % 16;
            if (offset < 0 || offset > log.size - 1) {
                printf("Invalid input.\n");
            } else {
                printf(COL_HEADER);
                while (offset < log.size) {
                    offset= print_data_row(offset, log.data, log.size);
                    
                    if (offset< log.size) {
                        printf("  --More--  ");
                        c = getchar();
                        if(c != '\n')
                            getchar(); //Consume trailing newline character
                    } else
                        printf("  EOF\n");
                    
                    switch (c) {
                        case 'e': 
                            printf("Select row and column to edit: ");
                            break;
                        case 'q':
                            printf("Quit blah.\n");
                            break;
                        default:
                            break;
                    }
                }
            }
            break;
        case 2:
            printf("Enter byte location (row and column)\n");
            int row = read_hex_number("Row: ");
            int column = read_hex_number("Column: ");
            break;
    }

    edit_data(&log, 3, 5, '2');

    return 0;

}

void get_file_info(struct log_t *log, char *filename)
{
    /*  Asks user for filename and attempts to open file. If successful, data from the file will be added to the log struct,
        as well as the size of the file in bytes.
    */
    FILE *fp = fopen(filename, "rb");
    char buffer[LEN];
    if (fp)
    {
        strcpy(buffer, filename);
    }
    else
    {
        while (!fp && strcmp(buffer, "quit"))
        {
            printf("Enter name of file to read (or type exit to quit): ");
            fgets(buffer, LEN, stdin);
            if (buffer[strlen(buffer) - 1] == '\n')
                buffer[strlen(buffer) - 1] = '\0';

            if (!strcmp(buffer, "quit"))
                printf("Exiting program.\n");
            else
            {
                fp = fopen(buffer, "rb");
                if (!fp)
                {
                    printf("Filename could not be found.\n");
                    *filename = '\0';
                }
            }
        }
    }
    strcpy(log->filename, buffer);
    fseek(fp, 0, SEEK_END);
    log->size = ftell(fp);
    rewind(fp);
    log->data = malloc(log->size + 1);
    fread(log->data, sizeof(char), log->size, fp);
    fclose(fp);
}

int print_data_row(int start, char *data, size_t size)
{
    int i;
    printf("%08x  ", start);
    for (i = start; i < (start + ROW_LEN); i++){
        if(i < size)
            printf("%02x ", data[i]);
        else
            printf("%2c ", ' ');
    }
    printf("  ");
    for (i = start; i < (start + ROW_LEN); i++)
    {
        if (!isprint(data[i]) || isspace(data[i]) || i > size)
            printf("%c", ' ');
        else
            printf("%c", data[i]);
    }
    return i;
}

int menu_selection(){
    int selection;
    printf("1. Enter offset\n2. Edit byte at specified row and column\n3. Undo changes\n4. Print all data\n5. Quit and save changes\n");
    do {
        selection = read_number("Input: ");
        if(selection < 1 || selection > 5)
            printf("Invalid input.\n");
    } while (selection < 1 || selection > 5);

    return selection;
    
}
void edit_data(struct log_t *log, int row, int column, int value)
{
    log->data[row * ROW_LEN + column] = value;
}

int read_number()
{
    int number = -1;
    char input[LEN];
    printf("Input: ");
    fgets(input, LEN, stdin);
    sscanf(input, "%d", &number);
    return number;
}

int read_hex_number(const char *prompt_text){
    int number;
    char input[LEN];
    char *ptr;
    printf("%s", prompt_text);
    fgets(input, LEN, stdin);
    sscanf(input, "%x", &number);
    return number;
}