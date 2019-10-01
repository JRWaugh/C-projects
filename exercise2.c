#include <stdio.h>
#define ARRAY_LENGTH 12

int calc_digits(int number);

int main() {
    float float_array[ARRAY_LENGTH], income, total = 0;
    printf("Enter yearly gross income\n");
    scanf("%f", &income);
    income /= 12.5;
    int digits = calc_digits((int)income);
    for(int i = 0; i < ARRAY_LENGTH; i++){
        if(i < 6 || i > 6){
            float_array[i] = income;
        } else {
            float_array[i] = income * 1.5;
        }
        printf("element [%2d] = %*.4f\n", i, digits, float_array[i]);
        total += float_array[i];
    }
    printf("%-13s", "total");
    printf("= %*.4lf\n", digits, total);
}

int calc_digits(int number) {
    int digits = 0;
    while(number > 0) {
        number /= 10;
        digits++;
    }
    return digits + 6;
}