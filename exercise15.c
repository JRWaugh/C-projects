#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h> // File size is huge because of ctype
#define BUF_SIZE 50

uint16_t crc16(const uint8_t* data_p, unsigned int length);
int read_number();
void read_string(char *string, int length);

struct chunk {
    uint8_t *data;
    uint16_t size;
    uint16_t capacity;
    uint16_t crc;
};

int main(){
    FILE *fp;
    struct chunk *chunks, *temp_chunks;
    char filename[BUF_SIZE], selection = 'y';
    int count = 0, data_size = -1;

    do {
        do {
            printf("Enter filename: ");
            read_string(filename, BUF_SIZE);  
            fp = fopen(filename, "rb");
            if(!fp)
                printf("Error reading file. Try again.\n");
        } while (!fp);

        do {
            printf("Enter chunk size: ");
            data_size = read_number();
            if(data_size <= 0)
                printf("Invalid input. Try again.\n");
        } while (data_size <= 0);

        //if(           chunks == NULL                              ||          chunks[0].data == NULL           )
        if( !((chunks = malloc((count + 1) * sizeof(struct chunk))) && (chunks[count].data = malloc(data_size))) ) {
            printf("Memory error. Terminating program.");
            return 1;
        }

        while(chunks[count].size = fread(chunks[count].data, 1, data_size, fp)) {
            chunks[count].capacity = data_size;
            count++;
            
            // Room is made for the next chunk
            // if temp_chunks != NULL && temp_chunks[count].data != NULL
            if( (temp_chunks = realloc(chunks, (count + 1) * sizeof(struct chunk))) && (temp_chunks[count].data = malloc(data_size)) ){
                chunks = temp_chunks;
            } else {
                printf("Memory error. Terminating program.");
                return 1;
            }
        } 
       
        //File operations are done so fp can be closed
        fclose(fp);

        //Print data chunks and free data memory allocations since they're no longer needed
        printf(" %s | %s (%s) | %s\n", "Chunk", "Size", "Max", "Checksum");
        for(int i = 0; i < count; i++) { 
            chunks[i].crc = crc16(chunks[i].data, chunks[i].size);
            printf(" %-6d| %4d (%3d) | %04x\n", i, chunks[i].size, chunks[i].capacity, chunks[i].crc);
            free(chunks[i].data);
        }

        //Free chunks (and temp_chunks) and reset count
        free(chunks);
        count = 0;
        
        do{
            printf("\nRead another file? y/n "); 
            selection = getchar();
            //Second getchar to eat newline character
            getchar();
            if(tolower(selection) != 'y' && tolower(selection) != 'n')
                printf("Invalid input.\n");
        } while (tolower(selection) != 'y' && tolower(selection) != 'n');

    } while (tolower(selection) == 'y');

    printf("Program ended.\n");
}

uint16_t crc16(const uint8_t* data_p, unsigned int length) {
    uint8_t x;
    uint16_t crc = 0xFFFF;
    while (length--){
        x = crc >> 8 ^ *data_p++;
        x ^= x>>4;
        crc = (crc << 8) ^ ((uint16_t)(x << 12)) ^ ((uint16_t)(x <<5)) ^ ((uint16_t)x);
    }
    return crc;
}

int read_number() {
    int number = 0;
    char input[BUF_SIZE];
    fgets(input, BUF_SIZE, stdin);
    if(sscanf(input, "%d", &number) == 1)
        return number;
    else
        return 0;
}

void read_string(char *string, int length) {
    fgets(string, length, stdin);
    if(string[strlen(string)-1] == '\n')  
        string[strlen(string)-1] = '\0';
}