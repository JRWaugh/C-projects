#include <stdio.h>
#include <string.h>
#define STOCK_LEN 20
#define LEN 50

struct price_info {
    double price;
    char name[LEN];
};

//This program reads price information from a file and populates an array of structs with it
int main(){
    char buffer[LEN];
    int count = 0, longest = 0;
    struct price_info stock[STOCK_LEN];

    printf("Input filename: ");
    fgets(buffer, LEN, stdin);
    if(buffer[strlen(buffer) - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0';

    FILE *fp = fopen(buffer, "r");
    if (fp == NULL)
        return 0;

    //Read items into struct array until end of file or until array is full
    while(!feof(fp) && count < STOCK_LEN){
        fgets(buffer, LEN, fp);
        //Increment count if both price and name are successfuly read from file
        if(sscanf(buffer, "%lf;%[^\n]", &stock[count].price, stock[count].name) == 2){
            if(strlen(stock[count].name) > longest)
                longest = strlen(stock[count].name);
            count++;
        } 
    }
    printf("Number of items found: %d\n", count);
    printf("%-*s %8s\n", longest, "Name", "Price");
    for(int i = 0; i < count; i++){
        printf("%-*s %8.2lf\n", longest, stock[i].name, stock[i].price);
    }
    return 0;
}