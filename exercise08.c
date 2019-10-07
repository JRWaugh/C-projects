#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define STR_LEN 50

void capitalise(char text[]);

int main() {
    char input[STR_LEN];
    do {
        printf("Enter text ('stop' to end)\n");
        fgets(input, STR_LEN, stdin);
        if(input[strlen(input)-1] == '\n') {
            input[strlen(input)-1] = '\0';
        }
        if(strcmp(input, "stop") && strcmp(input, "STOP")) {
            capitalise(input);
            printf("%s\n", input);
        }
    } while (strcmp(input, "stop") && strcmp(input, "STOP"));
}

void capitalise(char *text){
    *text = toupper(*text);
    while(*text != '\0') {
        if(isspace(*text++)){
            *text = toupper(*text);
        }
    }
}