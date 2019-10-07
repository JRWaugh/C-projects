#include <stdio.h>
#define LEN 20
#define DEBUG

#ifdef DEBUG
#define DEBUGMSG(fmt, ...) printf(fmt, __VA_ARGS__)
#else
#define DEBUGMSG(fmt, ...)
#endif

int main () {
    int numbers[5], result = 0;
    char buffer[LEN];
    printf("Enter 5 integers.\n");
    for(int i = 0; i < 5; i++){
        DEBUGMSG("%d ", i);
        do {
            printf("Input: ");
            fgets(buffer, LEN, stdin);
            result = sscanf(buffer, "%d", &numbers[i]);
            if(!result)
                printf("Invalid input.\n");
        } while (!result);
    }
}