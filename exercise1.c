#include <stdio.h>

int main() {
    int count = 0;
    double num = 0, total = 0;

    do {
        printf("Enter a positive number. Enter 0 to exit program\n");
        scanf("%lf", &num);
        if(num > 0) {
            total += num;
            count++;
        } else if (num < 0) {
            printf("Number must be positive\n");
        } else {
            printf("Exiting program\n");
        }
    } while(!num == 0);

    printf("Average is %lf", total / count);
}