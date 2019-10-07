#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STR_LEN 20
#define AB_LEN 26
#define A_INT 65
#define Z_INT 90

void caesar(char input[], int shift);

int main(){
    char message[STR_LEN];
    int shift;
    printf("Enter message you wish to encrypt:\n");
    fgets (message, STR_LEN, stdin);

    //Convert message to uppercase
    for(int i = 0; i < strlen(message); i++){
        message[i] = toupper(message[i]);        
    }
    
    if(message[strlen(message)-1] == '\n') {
        message[strlen(message)-1] = '\0';
    }

    printf("Enter desired shift for the encryption (integer):\n");
    scanf("%d", &shift);

    printf("Original message: %s\n", message);
    caesar(message, shift);
    printf("Encrypted message: %s\n", message);
    caesar(message, AB_LEN - shift);
    printf("Decrypted message: %s\n", message);
}

void caesar(char input[], int shift){
    //Adjust shift amount to be within -26 and 26
    if(shift % AB_LEN != 0)
        shift %= AB_LEN;

    for(int i = 0; i < strlen(input); i++){
        //Does not apply cipher to whitespace and special characters.
        if(isalpha(input[i])) {
            input[i] -= shift;
            if(input[i] < A_INT)
                input[i] += AB_LEN;
            else if(input[i] > Z_INT)
                input[i] -= AB_LEN;
        }       
    }
}