#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

int main() {
    FILE *fp;
    char *buffer, *temp_buffer;

    fp = fopen("exercise13.txt", "w");
    if(!fp) {
        printf("Error opening file.");
        return 1;
    }
    
    do { 
        int length = 16;

        //First attempt to read input into buffer array
        buffer = malloc(length * sizeof(char));
        printf("Enter a string ('.' to end program): ");
        fgets(buffer, length, stdin);

        //If input is greater than length, fgets will not have placed newline character at strlen()-1
        while(buffer[strlen(buffer)-1] != '\n'){
            //Realloc to temporary buffer so data is not lost if realloc fails
            if (temp_buffer = realloc(buffer, ++length * sizeof(char))) {
                buffer = temp_buffer;
                //Overwrite previous null terminator and continue adding data to the string. 
                //Will read one new character and then write new null character
                fgets(&buffer[strlen(buffer)], 2, stdin);
            } else {
                printf("Memory error. Printing partial input.\n");
                break;
            }
        }
        
        if(buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        
        if(*buffer != '.') {
            //fprintf returns negative number if there is an error during printing
            if(fprintf(fp, "%ld:%s\n", strlen(buffer), buffer) >= 0) {
                printf("\"%ld:%s\" successfully written to file.\n", strlen(buffer), buffer);
            } else {
                printf("Error writing to file.");
            }
        }
                  
    } while (*buffer != '.');

    free(buffer);
    fclose(fp); 
    printf("Program closed.\n"); 
    return 0;
}