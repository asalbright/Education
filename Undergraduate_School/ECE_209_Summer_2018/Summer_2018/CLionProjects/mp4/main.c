#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct card{
    int rank;
    char suit;
};

void printCard(struct card);
void printDeck(struct card deck[], int i);
int testHand(struct card deck[], int i);

int main() {

    struct card hand1[5];
    struct card hand2[5];

    /* hand 1 */
    hand1[0].rank = 1;
    hand1[1].rank = 2;
    hand1[2].rank = 3;
    hand1[3].rank = 10;
    hand1[4].rank = 10;

    hand1[0].suit = 'H';
    hand1[1].suit = 'S';
    hand1[2].suit = 'D';
    hand1[3].suit = 'C';
    hand1[4].suit = 'H';

    /* hand 2 */
    hand2[0].rank = 1;
    hand2[1].rank = 2;
    hand2[2].rank = 3;
    hand2[3].rank = 4;
    hand2[4].rank = 5;

    hand2[0].suit = 'H';
    hand2[1].suit = 'S';
    hand2[2].suit = 'D';
    hand2[3].suit = 'C';
    hand2[4].suit = 'H';

    printCard(hand1[3]);
    printf("\n");

    printDeck(hand1, 5);

    if(testHand(hand1, 5)) printf("hand1 has 1 pair\n");
    else printf("hand1 doesn't have 1 pair\n");

    if(testHand(hand2, 5)) printf("hand2 has 1 pair\n");
    else printf("hand2 doesn't have 1 pair\n");

//    printDeck(deck[], 4);

    return EXIT_SUCCESS;
}

void printCard(struct card card){
    if(card.rank > 9){
        if(card.rank == 10)
            printf("T");
        if(card.rank == 11)
            printf("J");
        if(card.rank == 12)
            printf("Q");
        if(card.rank == 13)
            printf("K");
    }
    else printf("%d", card.rank);

    printf("%c ", card.suit);

}

void printDeck(struct card deck[], int i){
    int count;
    for(count = 0; count < i; count++){
        printCard(deck[count]);
    }
    printf("\n");
}

int testHand(struct card deck[], int i){
    int pair = 0;
    int x;
    int card;
    for(x = 0; x < i; x++){
        card = deck[x].rank;
        int chk;
        for(chk = 0; chk < i; chk++){
            if(chk == x) chk++;
            if(chk == i) break;
            if(deck[chk].rank == card) pair++;
        }
    }

    if(pair == 2) {
        return 1;
    }
    else return 0;
}