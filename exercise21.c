#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STR_LEN 50
#define C_CHARS 128

struct character {
    unsigned char value;
    unsigned char occurrences;
};

int cmpoccur(const void *a, const void *b);

int main() {
    unsigned char buffer[STR_LEN], c;
    struct character characters[C_CHARS] = {0};
    FILE *fp;

    //Read filename until FILE pointer is opened
    do {
        printf("Enter name of file: ");
        fgets(buffer, STR_LEN, stdin);
        if(buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        fp = fopen(buffer, "rb");
    } while (!fp);

    //Read one character at a time
    while(fread(&c, sizeof(char), 1, fp)) {
        characters[c].value = c; //i.e. characters['a'].value = 'a', where 'a' = 97
        characters[c].occurrences++; 
    }

    qsort(characters, C_CHARS, sizeof(struct character), cmpoccur);

    printf("Most frequent characters in file %s:\n", buffer);
    printf("Chr | #\n");
    for(int i = 0; characters[i].occurrences && i < 10; i++){ //Until i == 10 or until occurrences == 0
        if(iscntrl(characters[i].value))
            printf(" %d | %d  (char is control code)\n",  characters[i].value, characters[i].occurrences);
        else
            printf("'%c' | %d\n", characters[i].value, characters[i].occurrences);
    }
}

int cmpoccur(const void *a, const void *b) {
    //Sorts character occurrences in descending order
    return ((struct character *)b)->occurrences - ((struct character *)a)->occurrences;
}