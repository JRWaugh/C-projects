#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 21

struct car_info {
    char make[LEN];
    char model[LEN];
    int price;
    float emissions;
};

struct file_info {
    char *data;
    long fsize;
};

int read_number();
void print_car_file(FILE *fp);
int write_car_to_file(struct car_info car, FILE *fp);
struct car_info create_car();
int read_db(struct file_info *file, char *filename);
struct car_info *db_to_arr(struct file_info file);

int main(){
    FILE *fp;
    struct file_info car_db;
    int selection, result;
    char filename[LEN];

    do {
        fp = fopen("cars.txt", "ab+");
        if(!fp){
            printf("Error opening file.");
            return 1;
        }
        fp = fopen("cars.txt", "ab+");
        printf("== Car Database ==\n1. Print all cars\n2. Write car to file\n3. Import cars from file\n4. Quit\n");
        selection = read_number();
        switch (selection) {
            case 1: 
                print_car_file(fp);
                break;
            case 2:
                if(write_car_to_file(create_car(), fp))
                    printf("Successful\n");
                else
                    printf("Error adding car to file.\n");cod
                break;
            case 3: 
                printf("Enter name of file to import data from: ");
                fgets(filename, LEN, stdin);
                if(filename[strlen(filename)-1] == '\n')
                    filename[strlen(filename)-1] = '\0';
            
                if(read_db(&car_db, filename)){
                    int i;
                    struct car_info *cars = db_to_arr(car_db);
                    for(i = 0; cars[i].price; i++)
                        write_car_to_file(cars[i], fp);
                    printf("%d cars read from database to file\n\n", i);
                    free(cars);
                }
                break;
            case 4:
                printf("Closing program.\n");
                break;
            default:
                printf("Invalid input.\n");
                break;
        }
        fclose(fp);
    } while (selection != 4);

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
    //Asks user for input and returns a car.
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

int read_db(struct file_info *file, char *filename){
    FILE *fp = fopen(filename, "r");
    if(fp){
        fseek(fp, 0, SEEK_END);
        file->fsize = ftell(fp);
        rewind(fp);
        file->data = malloc((file->fsize + 1) * sizeof(char));
        fread(file->data, 1, file->fsize, fp);
        fclose(fp);
        return 1;
    } else {
        printf("Could not open file with that name.\n");
        return 0;
    }
}

struct car_info *db_to_arr(struct file_info file){
    //Takes data from file_info struct and reads into car_info struct array

    int length = 0, count = 0;
    char *token = strtok(file.data, "}");
    struct car_info *cars = malloc((length + 1) * sizeof(struct car_info)); //Always make room for the terminating struct at least
    while(token && cars){
        char *make, *model, *price, *emissions;
        int result = 0;
        
        if(make = strstr(token, "make"))
            result += sscanf(make, "%*[^:]%*2c%[^\"]", cars[length].make); //All this sscanf formatting trouble just to strip the quotes from the strings
        if(model = strstr(token, "model"))
            result += sscanf(model, "%*[^:]%*2c%[^\"]", cars[length].model);
        if(price = strstr(token, "price"))
            result += sscanf(price, "%*[^:]:%d", &cars[length].price);
        if(emissions = strstr(token, "emissions"))
            result += sscanf(emissions, "%*[^:]:%f", &cars[length].emissions);

        if(result == 4){
            length++;
            cars = realloc(cars, (length + 1) * sizeof(struct car_info));
        } else {
            sscanf(token, "%*[^\"]%[^ ]", token); //Strip out ugly characters from token so it can be printed
            printf("Data error in entry %d of file. Missing car information.\n%s\n", count, (token));
        }
        count++;
        token = strtok(NULL, "}");
    }

    if(!cars){
        printf("Memory error.");
        return 0;
    }
    cars[length].price = 0; //Indicates where array ends
    return cars;
}