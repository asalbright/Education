#include <stdio.h>
#include <stdlib.h>

int numDigits(int);
void printDigit(int);
void allDigits(int);

int main() {
    int num;

    printf("Enter a positive decimal integer: ");
    fflush(stdout);
    scanf("%d", &num);

    printf("The number has %d digits.\n", numDigits(num));
    printf("The 1's digit is ");
    printDigit(num % 10);
    printf("\n");
    allDigits(num);
    printf("\n");
    return EXIT_SUCCESS;
}

int numDigits(int val) {
    int digit = 0;

    while(val != 0){
        val = val / 10;
        digit++;

    }
    return digit;
}

void printDigit(int digit) {
    while(digit > 10){
        digit = digit % 10;
    }
    if(digit == 0)
        printf("zero ");
    else if(digit == 1)
        printf("one ");
    else if(digit == 2)
        printf("two ");
    else if(digit == 3)
        printf("three ");
    else if(digit == 4)
        printf("four ");
    else if(digit == 5)
        printf("five ");
    else if(digit == 6)
        printf("six ");
    else if(digit == 7)
        printf("seven ");
    else if(digit == 8)
        printf("eight ");
    else if(digit == 9)
        printf("nine ");
    return;
}

void allDigits(int n) {
    int num = numDigits(n);
    int divide = 1;
    int var = n;

    while(num > 1) {
        divide = divide * 10;
        num--;
    }

    while(divide > 0){
        var = n;
        var = var / divide;
        printDigit(var);
        divide = divide / 10;
            }
    return;
}
