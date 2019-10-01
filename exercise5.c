#include <stdio.h>
#define SIZE 3

void matrix_mult(int result[SIZE], int vector[SIZE], int matrix[SIZE][SIZE]);

int main(){
    int vector[SIZE], 
        matrix[SIZE][SIZE],
        result[SIZE];

    printf("Enter values for vectors [%d x 1]: ", SIZE);
    for(int i = 0; i < SIZE; i++){
        scanf("%d", &vector[i]);
    }
    for(int i = 0; i < SIZE; i++){
        printf("Enter values for row %d of matrix [%d x %d]: ", i+1, SIZE, SIZE);
        for(int j = 0; j < SIZE; j++){
            scanf("%d", &matrix[i][j]);
        }      
    }
    matrix_mult(result, vector, matrix);
}

void matrix_mult(int result[SIZE], int vector[SIZE], int matrix[SIZE][SIZE]){
    printf("Vector: \n");
    int i = 0, j = 0;
    for(i = 0; i < SIZE; i++){
        printf("| %d |\n", vector[i]);
    }

    printf("Input matrix: \n");
    for(i = 0; i < SIZE; i++){
        printf("| ");
        result[i] = 0;
        for(j = 0; j < SIZE; j++){
            result[i] += matrix[i][j] * vector[j];   
            printf("%d ", matrix[i][j]);
        }

        printf("|\n");
    }

    printf("Result: \n");
    for(i = 0; i < SIZE; i++){
        printf("| %d |\n", result[i]);
    }
}