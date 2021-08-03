/*	Program Header:
	credit card validator
	Andrew A. September 2017
*/

#include <stdio.h>
#include <stdlib.h>

	int loopcount = 0;

int main()
{

	int readq = 0;				/*integer decleration*/
	int numofchar = 0;				
	int final = 0;					
	char ch = 0;					
	int convertInt;						
	int calcnum = 0;				
	int xval = 0;					
	int xint = 0;					
	int xcheck = 0;
	
	if(loopcount == 0){
	printf("Enter numbers, or 'q' to quit: \n");	/* prompt user */
	loopcount++;
	}

	while(ch != '\n'){				/* start while loop to test value*/
		ch = getchar();				/* get one character at a time from typed */
		numofchar++ ;				/* increase character counter by one each loop*/
		convertInt = (ch - 48);			/* change the got character to a decimal integer*/

		if((convertInt >= 0 && convertInt <= 9) && (numofchar % 2) != 0){	/* confirm number, confirm odd/even character counter */  
			convertInt = convertInt*2;					
				if(convertInt >= 9)
					convertInt = convertInt - 9;
			final = final + convertInt;					/*confirmed odd counter, *2. if > 9, -9. add value to final value */
		}

		else if((convertInt >= 0 && convertInt <= 9) && (numofchar % 2) == 0){	/* confirm number, confirm odd/even character counter*/
			
			final = final + convertInt;					/*confirmed even counter, add value to final value*/ 
		}	
		

		else if(ch == 0x71){ 							/* if q, increment q counter*/

			readq++;
		}
		else if(ch == 0x20) {							/* if space, decrement character counter*/

			numofchar-- ;
		}
		else if(ch == 'x' && numofchar == 16){					/*if x at the end, calculate numbers total before and calculate x value*/
			calcnum = final;
			xint = calcnum % 10;
				if(xint != 0){
					xval = (10 - xint);
					printf("%d\n", xval);
				}
				else{							/* if the value of x to be added is 0, xcheck = 1, and print a 0*/
	 				xcheck = 1;
					printf("0\n");
				}
		}
		else if(convertInt < 0 || convertInt > 9|| convertInt != 'q'){		/* if a character other than a number, q, or x in the 16th place is entered: break*/
				break;
		}		

		else if (ch == '\n') break;						/* if character got equals line feed: break*/

	}


		if(readq==1 && numofchar==2){						/* if q counter = 1 and character counter = 2, q is entered, exit program*/
		return EXIT_SUCCESS;
		}		


		if(ch == '\n'){								/* if linefeed was hit, check all following condidtions to set output*/
			final = final + xval;

			if(final % 10 == 0 && xval == 0 && xcheck != 1 && numofchar == 17){		/*final value is a multiple of 10, and an x was not typed, print ok*/
				printf("ok\n");
			}
			else if(final % 10 != 0 || numofchar != 17){					/*final value is not a multiple of 10, print bad*/
				printf("bad\n");
				return main();
			}

		}
	return main();
}
