#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define STR_LEN 50

void space_to_undescore(char text[]);

int main() {
    char input[STR_LEN];

    do {
        printf("Enter text ('stop' to end)\n");
        fgets (input, STR_LEN, stdin);

        if(input[strlen(input)-1] == '\n') {
            input[strlen(input)-1] = '\0';
        }

        space_to_undescore(input);
        printf("%s\n", input);
    } while (strcmp(input, "stop") && strcmp(input, "STOP"));
}

void space_to_undescore(char text[]){
    for(int i = 0; i < strlen(text); i++){
        if(isspace(text[i]))
            text[i] = '_';
    }
}