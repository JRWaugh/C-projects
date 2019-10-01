#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define LEN 12
#define ARRAY_LEN 15

int availability(struct rental cars[], int array_size, char plate[]);
void car_search(struct rental cars[], int array_size, char category, int print_all_cars);
void read_string(char *string);
int read_number();

struct rental {
    char make[LEN];
    char model[LEN];
    char category;
    char plate[LEN];
    int mileage;
    int available;
};

int main() {
    struct rental rentals[ARRAY_LEN] = {
        {"Ford", "Fiesta", 'C', "LGH-190", 10390, 1},
        {"Ford", "Focus", 'M', "ZHH-102", 8367, 0},
        {"BMW", "M3", 'P', "AGH-487", 13120, 1},
        {"BMW", "M4", 'M', "BJK-355", 3120, 1},
        {"Toyota", "Corolla", 'X', "PFF-421", 4560, 0},
        {"Toyota", "Camry", 'X', "OIO-909", 17801, 1},
        {"Nissan", "Altima", 'M', "STL-550", 2231, 0},
        {"Hyundai", "Accent", 'L', "PPQ-323", 7871, 0},
        {"Honda", "Accord", 'V', "LRT-781", 4021, 1},
        {"Mazda", "Mazda3", 'V', "VZD-202", 19220, 0},
        {"Mitsubishi", "Lancer", 'X', "TFA-834", 7112, 0},
        {"Nissan", "Armada", 'C', "QTY-211", 2354, 0},
        {"Mazda", "Mazda3", 'C', "HUJ-254", 6531, 1},
        {"Hyundai", "Elantra", 'P', "KLK-772", 11320, 1},
        {"Honda", "Civic", 'L', "JDL-112", 11786, 0},
    };
    int choice = 0, status = 0; 
    char input[LEN];
    do {
        printf("\n== RENTAL CAR DATABASE ==\n1. Print list of all cars\n2. Search available cars by category\n3. Edit car availability\n4. Quit\n");
        printf("Enter selection: ");
        choice = read_number();
        if (choice == 1) {
            car_search(rentals, ARRAY_LEN, '*', 1);  // 1 sets print_all_cars to true.
        } else if (choice == 2) {
            printf("Enter category [C, L, M, P, V, X] or enter * to see all available cars: ");
            read_string(input);
            car_search(rentals, ARRAY_LEN, *input, 0);  // Input is dereferenced to a character. 0 sets print_all_cars to false.
        } else if (choice == 3) {
            printf("Enter the plate number of car you wish to modify: ");
            read_string(input);
            if(status = availability(rentals, ARRAY_LEN, input)){
                printf("A car with license plate %s was found. It is now marked as ", input);
                if(status == 2)  
                    printf("available for hire.\n");
                else if(status == 1)  
                    printf("unavailable for hire.\n");
            } else {
                printf("No car with this license plate was found.\n");
            }
        } else if (choice == 4) {
            printf("Shutting down.\n");
        } else {
            printf("Invalid input.\n");
        }
    } while (choice != 4);
}

int availability(struct rental cars[], int array_size, char plate[]){
    // POSSIBLE THINGS TO ADD: convert lower case entries to upper, allow plates missing the '-' character to be readable as well.
    for(int i = 0; i < array_size; i++){
        if(!strcmp(cars[i].plate, plate))  
            return 1 + (cars[i].available = !cars[i].available); // returns 1 if found but now unvailable, 2 if found and now available.
    }
    return 0;
}

void car_search(struct rental cars[], int array_size, char category, int print_all_cars){
    printf("%-10s|%-7s|%-6s|%-7s|%8s\n", "Make", "Model", "Cat.", "Plate", "Mileage");
    for(int i = 0; i < array_size; i++){
        if( ((category == cars[i].category) || category == '*')  &&  (cars[i].available || print_all_cars) ) {
            printf("%-10s|%-7s|%-6c|%-7s|%8d\n", cars[i].make, cars[i].model, cars[i].category, cars[i].plate, cars[i].mileage);
        }
    }
}

void read_string(char *string){
    fgets(string, LEN, stdin);
    if(string[strlen(string)-1] == '\n')  
        string[strlen(string)-1] = '\0';
}

int read_number() {
    int number = 0;
    char input[LEN];
    fgets(input, LEN, stdin);
    sscanf(input, "%d", &number);
    return number;
}