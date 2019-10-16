#include <stdio.h>
#include <stdlib.h>
#define LEN 50
#define DESC_LEN 83 //82 because there needs to be space for \n, \0 and \r
#define DATE_LEN 15
struct transaction {
    int type; //Probably good idea to make income 1 and expenses -1
    char description[DESC_LEN];
    float amount;
    char date[DATE_LEN];
};

int main() {
    FILE *fp;
    int selection = 1, count_in_memory = 1;
    char input[LEN], filename[] = "expensetracker.txt";
    struct transaction *transactions;
    
    if(transactions = malloc(sizeof(struct transaction)))
        transactions[0].type = 0;
    else {
        printf("Program error.\n");
        return 0;
    }

    do {
        printf("1. Init\n2. Save\n3. Read file\n4. Add money\n5. Spend money\n6. Print report\n");
        do {
            printf("Selection: ");
            fgets(input, LEN, stdin);
        } while (sscanf(input, "%d", &selection) && (selection < 1 || selection > 6));

        switch (selection) {
            case 1:
                //Initialize
                free(transactions);
                transactions = malloc(sizeof(struct transaction));
                transactions[0].type = 0;

                //Unsure if this is also necessary
                if(fp = fopen(filename, "wb"))
                    fclose(fp);

                break;
            case 2:
                //Save to file
                //Currently this has the problem of not checking if the transactions in memory have already been written to the file
                if(fp = fopen(filename, "ab+")) {
                    fwrite(transactions, sizeof(struct transaction), count_in_memory, fp);
                    fclose(fp);
                } else {
                    printf("Error opening file.\n");
                }
                break;
            case 3:
                //Read from file
                if(fp = fopen(filename, "rb")) {
                    fseek(fp, 0, SEEK_END);
                    int count_in_file = ftell(fp) / sizeof(struct transaction);
                    fseek(fp, 0, SEEK_SET);

                    transactions = realloc(transactions, (count_in_file + count_in_memory) * sizeof(struct transaction));          
                    //Should either qsort based on date, or change this so the transactions read from file are first in the array.
                    fread(&transactions[count_in_memory], sizeof(struct transaction), count_in_file, fp);
                    count_in_memory += count_in_file;
                    fclose(fp);
                } else {
                    printf("Error reading from file.\n");
                }
                break;
            case 4:
                if(transactions = realloc(transactions, (count_in_memory + 1) * sizeof(struct transaction))){
                    transactions[count_in_memory].type = 1;

                    printf("Write a description: ");
                    fgets(transactions[count_in_memory].description, DESC_LEN, stdin);

                    do { 
                        printf("Enter amount: ");
                        fgets(input, LEN, stdin);
                    } while (!sscanf(input, "%f", &transactions[count_in_memory].amount)); //should check that this

                    printf("Enter date of transaction: ");
                    fgets(transactions[count_in_memory].description, DATE_LEN, stdin);
                } else {
                    printf("Memory error.\n");
                }
                break;
            case 5:
                //almost exactly the same as case 4...
                if(transactions = realloc(transactions, (count_in_memory + 1) * sizeof(struct transaction))){
                    transactions[count_in_memory].type = -1;

                    printf("Write a description: ");
                    fgets(transactions[count_in_memory].description, DESC_LEN, stdin);

                    do { 
                        printf("Enter amount: ");
                        fgets(input, LEN, stdin);
                    } while (!sscanf(input, "%f", &transactions[count_in_memory].amount)); //should check that this

                    printf("Enter date of transaction: ");
                    fgets(transactions[count_in_memory].description, DATE_LEN, stdin);
                } else {
                    printf("Memory error.\n");
                }
                break;
        }
    } while (1); //fix later
}