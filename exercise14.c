cod#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define DATA_SIZE 64
#define BUF_SIZE 50

uint16_t crc16(const uint8_t* data_p, unsigned int length);

struct chunk {
    uint8_t data[DATA_SIZE];
    uint16_t size;
    uint16_t crc;
};

int main(){
    FILE *fp;
    char filename[BUF_SIZE];
    int length = 0;
    struct chunk *chunks = malloc((length + 1) * sizeof(struct chunk));
    struct chunk *temp_chunks = chunks;

    do {
        printf("Enter filename: ");
        fgets(filename, BUF_SIZE, stdin);
        if (filename[strlen(filename) - 1] == '\n')
            filename[strlen(filename) - 1] = '\0';

        fp = fopen(filename, "rb");
        if(!fp)
            printf("Error reading file. Try again.\n"); 
    } while (!fp);

    while((chunks[length].size = fread(&chunks[length].data, 1, DATA_SIZE, fp)) == DATA_SIZE) {
        length++;
        if(temp_chunks = realloc(chunks, (length + 1) * sizeof(struct chunk)))
            chunks = temp_chunks;
        else {
            printf("Memory error. Printing partial results.");
            break;
        }
      
    }
        
    
    printf(" %s | %s | %s\n", "Chunk", "Size", "Checksum");
    for(int i = 0; i < length; i++){
        chunks[i].crc = crc16(chunks[i].data, chunks[i].size);
        printf(" %-6d|%5d | %04x\n", i, chunks[i].size, chunks[i].crc);
    }
    fclose(fp);
    free(chunks);
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