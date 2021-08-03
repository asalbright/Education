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
    return 0;
}

void printDigit(int digit) {
    printf("NOT DONE ");
    return;
}

void allDigits(int n) {
    printf("NOT DONE ");
    return;
}
