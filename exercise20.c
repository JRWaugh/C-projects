#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define PW_LEN 33

void generate_passw(char *output, int pw_size, const char **from_words);
int main(){
    const char *words[10] = {"Hello", "Surprise", "Bottle", "Bookshelf", "Table", "Magazine", "Paper", "Trees", "Cloth", "Pillar"};
    char passwords[3][PW_LEN];
    srand(time(NULL));

    for(int i = 0; i < 3; i++){
        generate_passw(passwords[i], PW_LEN, words);
        printf("%s\n", passwords[i]);
    }
}

void generate_passw(char *output, int pw_size, const char **from_words) {
    int pos, word; 
    do {
        pos = rand() % pw_size; // between 0 and 32
        word = rand() % 10; // between 0 and 9
    } while ((pos + strlen(from_words[word])) > pw_size);

    for(int i = 0; i < pw_size; i++){
        //printable characters are in ascii range 33 - 126 inclusive (94 characters)
        sprintf(&output[i], "%c", (rand() % 94) + 33);
    }

    strncpy(&output[pos], from_words[word], strlen(from_words[word]));
}