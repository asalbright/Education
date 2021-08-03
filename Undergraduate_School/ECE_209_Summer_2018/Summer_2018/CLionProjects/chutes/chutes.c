/* Andrew Albright
 * Program 1: Shoots n' Ladders
 * 07.01.2018
 */

#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

/*
 * FUNCTION Declarations
 */
void moveForward(int position[], int direction[], int i, int roll, int numOfPlayers);        /* Moves player forward */
void moveBackward(int position[], int direction[], int i, int roll, int numOfPlayers);      /* Moves player backward */
int chkLadderSlide(const int position[], int i, const int gBoard[]);                                         /* checks if place on board is a ladder/slide */
void climbLadder(int position[], int direction[], int i, const int gBoard[], int numOfPlayers);             /* Moves player up/down a ladder */
void decendSlide(int position[], int direction[], int i, const int gBoard[], int numOfPlayers);                    /* Moves a player down/up a slide */
int checkCollide(int const position[], int i, int numOfPlayers);                                   /* Checks if players collide */
void reversePlayer(int direction[], int i);                                                  /* Reverse the direction of a player */

/*
 * MAIN Function
 */
int main() {

    int WON = 0;                                                                             /* switch for exiting the game loop */

    int numOfPlayers = getNumPlayers();                                                      /* store the number of players in game */

    int position[4] = {0, BOARDSIZE+1, 0, BOARDSIZE+1};                                      /* position on the board of each player */
    int direction[4] = {1,-1,1,-1};                                                          /* direction of each player, 1 for forward, -1 for backward */


    while(!WON){                                                                             /* game loop */
        int rol = 0;        /* variable to hold the roll of players */
        int i = 0;
        for(i = 0; i < numOfPlayers; i++){                                               /* players turns loop */

            printf("\nPlayer %d's turn. ", i);
            rol = roll(i);                                                                   /* random roll generator */
            printf("Player %d's roll is %d. \nPlayer %d ", i, rol, i);

            if(i == 0 || i == 2){                                                            /* determines what direction EVEN players should move */
                if(direction[i] == 1){
                    moveForward(position, direction, i, rol, numOfPlayers);
                }

                else{
                    moveBackward(position, direction, i, rol, numOfPlayers);
                }
            }
            else if(i == 1 || i == 3){                                                      /* determines what direction ODD players should move */
                if(direction[i] == -1){
                    moveBackward(position, direction, i, rol, numOfPlayers);
                }
                else{
                    moveForward(position, direction, i, rol, numOfPlayers);
                }
            }

            if(chkLadderSlide(position, i, gBoard) == 1)                                    /* checks if player has landed at a ladder */
                climbLadder(position, direction, i, gBoard, numOfPlayers);
            else if(chkLadderSlide(position, i, gBoard) == -1)                              /* checks of player has landed at a slide */
                decendSlide(position, direction, i, gBoard, numOfPlayers);

            if(checkForWin(i, position, direction) == 1){                                    /* check for win */
                WON = checkForWin(i, position, direction);                                   /* flip the WON switch */
                printf("\nPlayer %d Won!\n", i);
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}

/*
 * FUNCTION Definitions
 */

/* function definition to move a player forward on the board (direction must be 1) */
void moveForward(int position[], int direction[], const int i, int roll, const int numOfPlayers){
    if(i == 0 || i == 2) {                              /* if moving player is an EVEN player, move forward if space is allocated */
        if ((position[i] + roll) <= BOARDSIZE) {
            printf("moves from position %d to ", position[i]);
            position[i] = position[i] + roll;
        }
        else printf("overshoots goal and returns to position ");
    }
    else{                                               /* if moving player is ODD, direction is backward and player must use the roll to reverse again */
        printf("moves from position %d to ", position[i]);
        while(position[i] < 100 && roll > 0){
            position[i]++;
            roll--;
        }
        if(position[i] == 100) reversePlayer(direction, i);

        while(roll > 0){
            position[i]--;
            roll--;
        }
    }
    printf("%d.\n", position[i]);                       /* print the landed position at the end of the previous sentence */

    if(checkCollide(position, i, numOfPlayers)){        /* if player collides with another player, reverse player */
        reversePlayer(direction, i);
    }
}

/* function definition to move a player backward on the board (direction must be -1) */
void moveBackward(int position[], int direction[], const int i, int roll, const int numOfPlayers){
    if(i == 1 || i == 3) {                              /* if moving player is an ODD player, move backward if space is allocated */
        if ((position[i] - roll) >= 1) {
            printf("moves from position %d to ", position[i]);
            position[i] = position[i] - roll;
        }
        else printf("overshoots goal and returns to position ");
    }
    else{                                               /* if moving player is EVEN, direction is backward and player must use the roll to reverse again */
        printf("moves from position %d to ", position[i]);
        while(position[i] > 1 && roll > 0){
            position[i]--;
            roll--;
        }

        if(position[i] == 1) reversePlayer(direction, i);

        while(roll > 0){
            position[i]++;
            roll--;
        }
    }
    printf("%d.\n", position[i]);                       /* print the landed position at the end of the previous sentence */

    if(checkCollide(position, i, numOfPlayers)){        /* if player collides with another player, reverse player */
        reversePlayer(direction, i);
    }
}

/* function definition to check of position of player is at base/top of ladder/slide; RETURNS: 1 if ladder, -1 if slide */
int chkLadderSlide(const int position[], int i, const int gBoard[]){
    int ret = 0;

    if(gBoard[position[i]] != 0){
        if(gBoard[position[i]] > position[i])
            ret = 1;
        else if(gBoard[position[i]] < position[i])
            ret = -1;
    }
    return ret;
}

/* function definition to move a player up/down a ladder; check for collision */
void climbLadder(int position[], int direction[], int i, int const gBoard[], int numOfPlayers){
    int temp = position[i];                                                             /* temp variable to relpace if collision occurs */
    printf("Ladder encountered, player %d ascends to position %d.\n", i, gBoard[position[i]]);
    position[i] = gBoard[position[i]];

    if(checkCollide(position, i, numOfPlayers)){
        printf("Player %d decends the ladder to position %d due to the reversal.\n", i, temp);
        position[i] = temp;
        reversePlayer(direction, i);
    }
}

/* function definition to move a player down/up a slide; checks for collision */
void decendSlide(int position[], int direction[], int i, const int gBoard[], int numOfPlayers){
    int temp = position[i];
    printf("Slide encountered, player %d decends to position %d.\n", i, gBoard[position[i]]);
    position[i] = gBoard[position[i]];

    if(checkCollide(position, i, numOfPlayers)){
        printf("Player %d ascends the slide to position %d due to the reversal.\n", i, temp);
        position[i] = temp;
        reversePlayer(direction, i);
    }
}

/* function definition to check if players collide; returns 1 if collision occurs, else return 0  */
int checkCollide(int const position[], int i, int numOfPlayers){
    int ret = 0;
    int chk;
    for(chk = 0; chk < numOfPlayers; chk++){
        if(chk == i) chk++;
        if(position[i] == position[chk]){
            printf("Player %d collided with Player %d, player %d changes direction.\n", i, chk, i);
            ret = 1;
        }
    }
    return ret;
}

/* function definition to reverse a players direction */
void reversePlayer(int direction[], int i){
    direction[i] = !direction[i];
}


/* Notes:
 *
 * Ladders: Good for Even, Bad for Odd; Location(s): gBoard[2, 4, 9, 21, 28, 36, 51, 71, 80, 87]
 * Slides: Good for Odd, Bad for Even; Location(s): gBoard[16, 47, 49, 56, 62, 64, 93, 95, 98]
 * Seed: 3571
 */
