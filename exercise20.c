#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define PW_LEN 32
#define WORDCOUNT 10

void generate_passw(char *pw_output, int pw_size, const char **secret_words);
int main(){
    const char *words[WORDCOUNT] = {"Hello", "Surprise", "Bottle", "Bookshelf", "Table", "Magazine", "Paper", "Trees", "Cloth", "Pillar"};
    char passwords[3][PW_LEN];
    srand(time(NULL));

    for(int i = 0; i < 3; i++){
        generate_passw(passwords[i], PW_LEN, words);
        printf("%s\n", passwords[i]);
    }
}

void generate_passw(char *pw_output, int pw_size, const char **secret_words) {
    int word = rand() % WORDCOUNT; // Choose a random word from secret_words
    int pos = rand() % (pw_size - 1 - strlen(secret_words[word])); // Find a position for the random word   

    for(int i = 0; i < pw_size - 1; i++){
        pw_output[i] = (rand() % 94) + 33; //printable characters are in ascii range 33 - 126 inclusive (94 characters)
    }
    pw_output[pw_size - 1] = '\0'; //Password is null terminated
    strncpy(&pw_output[pos], secret_words[word], strlen(secret_words[word]));
}