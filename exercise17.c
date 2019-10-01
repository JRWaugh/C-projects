#include <stdio.h>
#include <string.h>
#define LEN 21

struct car_info {
    char make[LEN];
    char model[LEN];
    int price;
    float emissions;
};

int read_number();
void print_car_file(FILE *fp);
int write_car_to_file(struct car_info car, FILE *fp);
struct car_info create_car();

int main(){
    FILE *fp = fopen("cars.txt", "ab+");
    struct car_info car;
    int selection;

    if(!fp){
        printf("Error opening file.");
        return 1;
    }
    
    do {
        fp = fopen("cars.txt", "ab+");
        printf("== Car Database ==\n1. Print all cars\n2. Add car to file\n3. Quit\n");
        selection = read_number();
        switch (selection) {
            case 1: 
                print_car_file(fp);
                break;
            case 2:
                if(write_car_to_file(create_car(), fp))
                    printf("Successful\n");
                else
                    printf("Error adding car to file.\n");
                break;
            case 3:
                printf("Closing program.");
                break;
            default:
                printf("Invalid input.");
                break;
        }
        fclose(fp);
    } while (selection != 3);

    return 0;
}

int read_number() {
    int number = 0;
    char input[LEN];
    printf("Input: ");
    fgets(input, LEN, stdin);
    sscanf(input, "%d", &number);
    return number;
} 

void print_car_file(FILE *fp){
    struct car_info car;
    printf("%-10s|%-8s|%-7s|%-9s\n", "Make", "Model", "Price", "Emission");
    while(fread(&car, sizeof(struct car_info), 1, fp))
        printf("%-10s|%-8s|%-7d|%-9.2f\n", car.make, car.model, car.price, car.emissions);
}

int write_car_to_file(struct car_info car, FILE *fp){
    if(fwrite(&car, sizeof(struct car_info), 1, fp))
        return 1;
    else
        return 0;
}

struct car_info create_car(){
    struct car_info car;
    char buffer[LEN];

    printf("Enter car make: ");
    fgets(car.make, LEN, stdin);
    if(car.make[strlen(car.make)-1] == '\n')
        car.make[strlen(car.make)-1] = '\0';

    printf("Enter car model: ");
    fgets(car.model, LEN, stdin);
    if(car.model[strlen(car.model)-1] == '\n')
        car.model[strlen(car.model)-1] = '\0';

    printf("Enter price of car: ");
    fgets(buffer, LEN, stdin);
    if(sscanf(buffer, "%d", &car.price) != 1)
        car.price = 0;

    printf("Enter car emissions: ");
    fgets(buffer, LEN, stdin);
    if(sscanf(buffer, "%f", &car.emissions) != 1)
        car.emissions = 0;
    
    return car;
}




