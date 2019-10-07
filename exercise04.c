#include <stdio.h>
#define LENGTH 20
int main(){
    char input[LENGTH];
    int hh = -1, mm = -1, s_hh = -1, s_mm = -1;
    do {
        printf("Enter current time (hh:mm):\n");
        fgets(input, LENGTH, stdin);
        sscanf(input, "%d:%d", &hh, &mm);
        if((hh > 23 || hh <= 0) || (mm > 59 || mm <= 0)) {
            printf("Error! Invalid input.\n");
        }
    } while ((hh > 23 || hh <= 0) || (mm > 59 || mm <= 0));

    do {
        printf("How long do you want to sleep (h:mm):\n");
        scanf("%d:%d", &s_hh, &s_mm);
        if((s_hh > 9 || s_hh <= 0) || (s_mm > 59 || s_mm <= 0)) {
            printf("Error! Invalid input.\n");
        }
    } while ((s_hh > 9 || s_hh <= 0) || (s_mm > 59 || s_mm <= 0));

    int t_hh = hh + s_hh;
    int t_mm = mm + s_mm;
    if(t_mm > 59){
        t_mm -=60;
        t_hh++;
    }
    if(t_hh > 23)
        t_hh -= 24;
    printf("If you went to bed now you must wake up at %02d:%02d\n", t_hh, t_mm);
}