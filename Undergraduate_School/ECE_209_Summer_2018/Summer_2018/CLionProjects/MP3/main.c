#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strreverse(char *dest, const char *src);
int isPalindrome(const char *str);

int main() {
    char input[100] = "";
    char output[100] = "";

    char *pIn = input;
    char *pOut = output;


    printf("Enter a string:\n");

    scanf("%99s", pIn);
    strreverse(pOut, pIn);

    printf("%s\n", pOut);

    if(isPalindrome(pIn)) printf("Yes\n");
    else printf("No\n");

    return EXIT_SUCCESS;
}

char *strreverse(char *dest, const char *src){

    int num = 0;

    while(*src != '\0'){
        src++;
        num++;
    }
    src--;

    while(num > 0){

        *dest = *src;
        dest++;
        src--;
        num--;
    }
    *dest = '\0';

    return dest;
}

int isPalindrome(const char *str){

    int check = 0;
    const char *p1 = str;
    const char *p2 = str;

    while(*p2 != '\0') p2++;
    p2--;

    while(*p1 == *p2){
        p1++;
        p2--;

        if(p1 == (p2-1) && *p1 == *p2) return !check;
        if(p1 == p2) return !check;
    }
    return check;
}
