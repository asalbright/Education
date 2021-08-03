#include <stdio.h>

int main() {

    int var;
    int num = 1;

    printf("Enter a number: ");
    scanf("%d", &var);
    printf("The factors of %d are:\n", var);

    while(num <= var){
        if((var % num) == 0)
            printf("%d ", num);
            num++;

    }
    return 0;
}