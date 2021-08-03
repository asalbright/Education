/* Program Header:
 * Program takes entered base and entered number and translates it into Decimal, Hex, and Bianary form.
 * Andrew Albright
 * May 23, 2018
*/

#include <stdio.h>
#include <stdlib.h>

int main() {

    int chk = 1;        /* int to keep loops flowing */
    char ch;            /* char to take one char from std input stream */

    while (chk == 1) {
        int badch = 0;      /* int to count number of bad characters found */
        int base;       /* int to hold base number */
        int num = 0;    /* int to be created from ch and used to calculate result */
        int result = 0; /* int to store result decimal number */

        printf("Enter the base (2-36), 0 to quit: ");       /* Base entered must be a numeric value, nothing else will be entered */

        scanf("%d", &base);

        if (base == 0)                                      /* if base is 0, hault program */
            return EXIT_SUCCESS;

        else if (base >= 2 && base <= 36) {                 /* if base is within range, step into functions and find values */

            printf("Enter the base %d value: ", base);      /* Value entered needs to be cleared by the base entered (i.e. if base entered is
 *                                                             12, value must be < b) */

            scanf("%c", &ch);                               /* This scanf() gets rid of the linefeed left on the standard input stream from the base entry */

            while (chk == 1) {

                scanf("%c", &ch);                          /* Takes a single char from Std Input Stream; Value entered must be a numeric/alphabetical character */

                if(ch == '\n')                             /* if ch equals a linefeed character, break loop */
                    break;

                else if(ch >= '0' && ch <= '9')            /* if ch is a number, convert to its decimal value */
                    num = ch - 48;

                else if(ch >= 'A' && ch <= 'Z')             /* if ch is a uppercase letter, convert to its decimal value */
                    num = ch - 55;

                else if(ch >= 'a' && ch <= 'z')             /* if ch is a lowercase letter, convert to its decimal value */
                    num = ch - 87;

                else {                                                      /* if ch isn't a proper character print statement and break loop */
                    badch++;                                                /* increments the number of bad characters found */
                    printf("Bogus character %c -- value ignored\n", ch);
                    while(ch != '\n')                                       /* clears std input stream of all remaining characters bogus or not */
                        scanf("%c", &ch);
                    break;
                }

                if(num >= base){                                            /* checks to make sure the values entered are all legal according to base, if not break loop */
                    badch++;                                                /* increments the number of bad characters found */
                    printf("Bogus character %c -- value ignored\n", ch);
                    while(ch != '\n')                                       /* clears std input stream of all remaining characters bogus or not */
                        scanf("%c", &ch);
                    break;
                }

                result = result * base + num;               /* compute the total value which will be decimal */

                if(result > 65536) {                        /* if value ever breaches the max decimal allowed, stop computing and prompt for new base */
                    while(ch != '\n')
                        scanf("%c", &ch);
                    break;
                }
            }

            if(result > 65536)                                    /* prints error message for values too large */
                printf("ERROR: value out of range\n");

            else if (ch == '\n' && badch == 0) {                  /* if linefeed has been read and no bogus characters were entered, the value(s) can be printed */

                printf("Decimal: %d\n", result);

                printf("Hexadecimal: 0x%x\n", result);

                printf("Binary: ");
                int x, y;
                for(x = 15; x >= 0; x--){                         /* converts decimal num to binary through bit-shifting and AND operation check */
                    y = result >> x;
                    if(y & 1)
                        printf("1");
                    else
                        printf("0");
                }
                printf("\n");                                   /* prints linefeed to keep the conversation flowing */
            }
        }
    }

}
