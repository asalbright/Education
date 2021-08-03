/*
 * 
 * File:   tools.c
 * Author: gbyrd
 *
 * ECE 209, Summer 2018
 * 
 * Functions related to game play.
 * 
 */

#include <stdio.h>   /* printf, scanf */
#include <stdlib.h>  /* rand, srand */

#include "tools.h"

/* This is the board from the Hasbro "Chutes and Ladders" game,
 * except can't have a ladder in square 1 (because 1 is the goal
 * for odd players)
 */
const int gBoard[BOARDSIZE+1] =
{ 0,  /* note: slot 0 is not used */
  0, 38, 0, 14, 0, 0, 0, 0, 31, 0,   /* 1-10 */
  0, 0, 0, 0, 0, 6, 0, 0, 0, 0,    /* 11-20 */
  42, 0, 0, 0, 0, 0, 0, 84, 0, 0,    /* 21-30 */
  0, 0, 0, 0, 0, 44, 0, 0, 0, 0,    /* 31-40 */
  0, 0, 0, 0, 0, 0, 26, 0, 11, 0,    /* 41-50 */
  67, 0, 0, 0, 0, 53, 0, 0, 0, 0,    /* 51-60 */
  0, 19, 0, 60, 0, 0, 0, 0, 0, 0,    /* 61-70 */
  91, 0, 0, 0, 0, 0, 0, 0, 0, 100,    /* 71-80 */
  0, 0, 0, 0, 0, 0, 24, 0, 0, 0,    /* 81-90 */
  0, 0, 73, 0, 75, 0, 0, 78, 0, 0     /* 91-100 */
};



/* global variables, for this file only */
static int gNumP = 0;  /* number of players participating in this game */
static int gRndSeed = 0;  /* random number seed */

/* returns number of players for this game,
 * gets value from user if number of players not set
 */
int getNumPlayers() {
   int n = 0;
   if (gNumP == 0) {
      do {
         printf("Enter number of players (1-4): ");
         fflush(stdout);
         scanf("%d", &n);
      } while ((n < 1) || (n > 4));
      gNumP = n;
      scanf("%*c");  /* get rid of LF character */
   }
   return gNumP;
}

/* gets next move for player, random roll of die
 */
int roll(int player) {
   
   /* plsyer parameter is not used in this version,
    * but it might be useful for testing purposes
    */
   
   char bogus = '\0';

   /* if first time, seed random number generator */
   if (gRndSeed == 0) {
      gRndSeed = 3571;  /* a prime number */
      /* change seed to get a different sequence of random numbers */
      srand(gRndSeed);
   }
   
   /* make user hit ENTER to roll die */
   /* comment this part out to make it less interactive */
   printf("(Hit enter to roll die.)");
   do {
      scanf("%c", &bogus);
   } while (bogus != '\n');
   
   return 1 + rand()%6;
}

/* checks whether player is a winner,
 * based on positions array
 */
int checkForWin(int player, int positions[], int directions[]) {
   /* directions is unused here, but may be useful for testing */

   /* if player is even, winning square is BOARDSIZE,
    * else winning square is 1
    */
   int square = positions[player];
   int win = 0;
   if (player%2 == 0) win = (square == BOARDSIZE);
   else win = (square == 1);
   return win;
}

