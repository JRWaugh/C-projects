#include <stdio.h>
#define LEN 20

int main () {
    double num = 0, total = 0;
    int count = 0, read = 0;
    char buffer[LEN];
    FILE *fp = fopen("exercise10.txt", "r");
    if (fp == NULL)
        return 0;
    
    //Read first line to find count
    fgets(buffer, LEN, fp);
    sscanf(buffer, "%d", &count);

    while(fgets(buffer, LEN, fp) != NULL){
        //Add to total and increment read if fscanf is successful
        if(sscanf(buffer, "%lf", &num) == 1){
            total += num;
            read++;
        }
    }
    fclose(fp);

    if(read != count){
        printf("Error! Expected to read %d numbers. %d numbers were read.\n", count, read);
        
    printf("Average of %d numbers is %.2lf\n", read, total / read);
    }
    return 0; 
}