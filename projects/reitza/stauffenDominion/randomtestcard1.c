/*******************************************
  Random test village
********************************************/
/*#include "dominion_helpers.h"
#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define CARD village

int checkVillage(int card, struct gameState *post,int p, int handPos){
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  int choice1=1, choice2=1, choice3=1;
  int r,i, deckTreasure, discardTreasure;
  int errorHandCount, errorDeckDisCount, errorPlayedCount, errorActionCount;
    
  r = cardEffect(card, choice1, choice2, choice3, post, handPos, &handPos);

  errorPlayedCount=errorHandCount=errorPlayedCount=errorActionCount=errorDeckDisCount=0;

  //check found Count or Card errors
  if(pre.deckCount[p]+pre.discardCount[p]>=1){//Test for two treasures picked up 
    if(post->handCount[p]!=pre.handCount[p])
      errorHandCount=1;
    if(post->deckCount[p]+post->discardCount[p]!=pre.deckCount[p]+pre.discardCount[p]-1)
      errorDeckDisCount=1;
  } 

  //check played card count
  if(post->numActions!=pre.numActions+2)
    errorActionCount=1;
  if(post->playedCardCount!=pre.playedCardCount+1)
    errorPlayedCount=1;

  //Print error messages.
  if(errorActionCount|| errorPlayedCount || errorHandCount || errorDeckDisCount){
    printf("***************ERROR***************************************\n");
    if(errorPlayedCount)
      printf("ERROR: Played card not added to played pile\n");
    if(errorHandCount)
      printf("ERROR: Hand count not incremented correctly\n");
    if(errorDeckDisCount)
      printf("ERROR: Deck + Discard count is incorrect\n");
    if(errorActionCount)
      printf("ERROR: Action count not incremented correctly\n");
    printf("Pre-HandCount: %d   Post-HandCount %d\n", pre.handCount[p], post->handCount[p]);
    printf("Pre-Deck+Discard: %d   Post-Deck+Discard %d\n", pre.deckCount[p]+pre.discardCount[p], post->discardCount[p]+post->deckCount[p]);
    printf("Note: Actions is still to be decremented by playcard function\n");
    printf("Pre-ActionCount:%d   Post-ActionCount:%d\n", pre.numActions, post->numActions);
    printf("Pre-Discard+Deck Treasure: %d\n", discardTreasure+deckTreasure);
    printf("***********************************************************\n");
  }
  return 0;
}

int containsCard(int p, int card, struct gameState *G){

  return 0;
}

int main () {

  int i, n, r, p, c, deckCount, discardCount, handPos, handCount;
  int tempSupply;

  struct gameState G;
  int supply[16];

  printf ("*********************\n    Testing Adventurer\n*********************.\n");

  printf ("    **Random Testing**\n");

  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = rand()%256;
    }
    
    G.whoseTurn= p = rand()%2; //Randomize player turn
    G.deckCount[p] = rand()%MAX_DECK; //Randomize deck count 
    G.discardCount[p] = rand()%MAX_DECK; //Randomize discard count
    G.handCount[p] = rand()%MAX_HAND; //Randomize hand count
    G.playedCardCount = rand()%5;
    if(G.handCount[p]==0)
	   G.handCount[p]++;


    for (i = 0; i < G.handCount[p]; i++) {
        G.hand[p][i] = rand() % 17;
    }
    for (i = 0; i < MAX_DECK; i++) {
      if (i < G.deckCount[p]) {
        G.deck[p][i] = rand() % 17;
      }
      else {
        G.deck[p][i] = -1;
      }
    }
    for (i = 0; i < MAX_DECK; i++) {
      if (i < G.discardCount[p]) {
        G.discard[p][i] = rand() % 17;
      }
      else {
        G.discard[p][i] = -1;
      }
    }

    handPos =-1;
    //check players hand for CARD, if not there then put it in hand
    for (i = 0; i < G.handCount[p]; i++) {
      if (G.hand[p][i] == CARD) {
        handPos = i;
        i = G.handCount[p];
      }
    }//put CARD into players hand if not there
    if (handPos == -1) { 
      handPos = rand() % G.handCount[p];
      G.hand[p][handPos] = CARD;
    }

    checkVillage(CARD, &G, p, handPos);
  }

  return 0;
}



