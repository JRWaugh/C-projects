#include <stdio.h>
#define LEN 3
// This program reads 3 numbers from a file, rearranges them in ascending order, and then rewrites them to the file.
int main () {
    int number[LEN], i = 0, j = 0, dummy = 0;
    FILE *fp = fopen("exercise11.txt", "r+");
    if (fp == NULL)
        return 1;
        
    //Read the numbers from file to array
    for(int i = 0; i < LEN; i++)
        fscanf(fp, "%d", &number[i]);
        
    fclose(fp);

    //Rearrange the numbers
    for (i = 0; i < LEN; i++)
        for (j = i + 1; j < LEN; j++)
            if (number[i] > number[j]) {
                dummy = number[i];
                number[i] = number[j];
                number[j] = dummy;
            }

    //Seek to first line of file so that new numbers can be written over old numbers
    fseek(fp, 0, SEEK_SET); 
    for (i = 0; i < LEN; i++)
        fprintf(fp, "%d\n", number[i]);
    
    return 0;
}