#include <stdio.h>
#define LENGTH 40

float average_calc(int grades[], int size);

int main() {
    int grades[LENGTH], students = 0, grade = 0;
    do {
        printf("How many students are to be graded?\n");
        scanf("%d", &students);
        if(students > LENGTH){
            printf("Number of students cannot exceed %d!\n", LENGTH);
        }
    } while (students > LENGTH);

    for(int i = 0; i < students; i++){
        printf("Enter grade (range 0-5) for student %d\n", i + 45000);
        scanf("%d", &grades[i]);
        if(grades[i] < 0 || grades[i] > 5){
            printf("Invalid grade!\n");
            i--;
        }
    }    
    float average = average_calc(grades, students);
    printf("%.2f", average);
}

float average_calc(int grades[], int size) {
    float average = 0;
    for(int i = 0; i < size; i++){
        average += grades[i];
    }
    return average / size;
}