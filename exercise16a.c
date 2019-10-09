#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STR_LEN 50

int read_number();

int main() {
    FILE *fp;
    char filename[STR_LEN];
    char *data;
    long file_size;
    int offset = 0, amount = 0;
    do {
        printf("Enter name of file to read: ");
        fgets(filename, STR_LEN, stdin);
        if (filename[strlen(filename) - 1] == '\n')
            filename[strlen(filename) - 1] = '\0';

        fp = fopen(filename, "rb");

        if(!fp)
            printf("File could not be found.");
    } while (!fp);

    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);
 
    printf("File Size: %ld Bytes\n", file_size);
    do {
        //In this loop, file_size is treated as an array index so 1 is substracted from it
        printf("Enter offset (0 - %ld): ", file_size - 1);
        offset = read_number();
        if(offset < 0 || offset > file_size - 1)
            printf("Input out of range.\n");
    } while(offset < 0 || offset > file_size - 1);

    do {
        //In this loop, file_size (and amount) are treated as the number of bytes in the array, so 1 is not subtracted from it
        printf("Enter number of bytes to remove: ");
        amount = read_number();
        if(amount + offset > file_size)
            printf("Sum of starting byte and amount to remove exceeds data.\n");
        else if(amount < 0)
            printf("Error. Enter positive value.\n");
    } while ( (amount + offset > file_size) || amount < 0);

    if(data = malloc((file_size - amount) * sizeof(char))) {
        fread(data, sizeof(char), offset, fp);
        fseek(fp, amount, SEEK_CUR);
        fread(data + offset, sizeof(char), file_size - offset - amount, fp);
        fclose(fp);
    } else {
        printf("Error reading file data into memory");
        return 1;
    }

    if(fp = fopen(filename, "wb")){
        fwrite(data, sizeof(char), file_size - amount, fp);
        free(data);
        fclose(fp);
    } else 
        printf("Error making changes to file.\n");
    return 0;
}

int read_number() {
    int number = 0;
    char input[STR_LEN];
    fgets(input, STR_LEN, stdin);
    sscanf(input, "%d", &number);
    return number;
}