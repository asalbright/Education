/* 
 * File:   tools.h
 * Author: gbyrd
 *
 * ECE 209, Summer 2018
 * 
 * Functions and macros related to game play.
 * 
 */

/***** global game parameters *****/

#define MAXPLAYERS 4   /* number of players allowed */
#define BOARDSIZE 100  /* number of squares on the board */
extern const int gBoard[BOARDSIZE+1];  /* board array -- defined in tools.c */

/***** game functions *****/

/* return number of players for this game,
 * will be between 1 and MAXPLAYERS
 */
int getNumPlayers();

/* return result of next roll of die
 * for designated player,
 * will be between 1 and 6
 */
int roll(int player);

/* checks result of previous move
 * for designated player,
 * returns 1 if player wins, 0 otherwise
 * 
 * positions[] is the array of positions
 * for all players (size = MAXPLAYERS)
 * 
 * Player 1 is in positions[0], etc.
 */
int checkForWin(int player, int positions[], int directions[]);

