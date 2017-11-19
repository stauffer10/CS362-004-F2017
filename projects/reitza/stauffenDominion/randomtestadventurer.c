/*******************************************
  Random test Adventurer
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

#define CARD adventurer
#define DEBUG 1 

int checkAdventurer(int card, struct gameState *post,int p, int handPos){
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  int choice1=1, choice2=1, choice3=1;
  int r,i, deckTreasure, discardTreasure;
  int errorHandCount, errorTreasure, errorDeckDisCount, errorPlayedCount, last, scndToLast;
    
  r = cardEffect(card, choice1, choice2, choice3, post, handPos, &handPos);

  last = post->hand[p][post->handCount[p]-1];
  scndToLast = post->hand[p][post->handCount[p]-2];

  deckTreasure=errorTreasure=discardTreasure=errorPlayedCount=0;
  //check deck for treasure cards
  for(i=0; i < pre.deckCount[p] ; i++){
    if(pre.deck[p][i] >= copper || pre.deck[p][i] <= gold)
      deckTreasure++;
  }
  for(i=0; i < pre.discardCount[p] ; i++){
    if(pre.deck[p][i] >= copper || pre.deck[p][i] <= gold)
      discardTreasure++;
  }

  //check found Count or Card errors
  if(deckTreasure+discardTreasure>=2){//Test for two treasures picked up 
    if(post->handCount[p]!=pre.handCount[p]+1)
      errorHandCount=1;
    if(post->deckCount[p]+post->discardCount[p]!=pre.deckCount[p]+pre.discard[p]-2)
      errorDeckDisCount=1;
    if(last < copper && last > gold)
      errorTreasure=1;
    if(scndToLast < copper && scndToLast > gold)
      errorTreasure=1;
  } else if (deckTreasure+discardTreasure==1){//Test for one treasure picked up
    if(post->handCount[p]!=pre.handCount[p])
      errorHandCount=1;
    if(post->deckCount[p]+post->discardCount[p]!=pre.deckCount[p]+pre.discard[p]-1)
      errorDeckDisCount=1;
    if(last < copper && last > gold)
      errorTreasure=1;
  } 
  //check played card count
  if(post->playedCardCount!=pre.playedCardCount+1)
    errorPlayedCount=1;

  //Print error messages.
  if(errorTreasure|| errorPlayedCount || errorHandCount || errorDeckDisCount){
    printf("***************ERROR***************************************\n");
    if(errorTreasure)
      printf("ERROR: Treasure cards not added to hand correctly\n");
    if(errorPlayedCount)
      printf("ERROR: Played card not added to played pile\n");
    if(errorHandCount)
      printf("ERROR: Hand count not incremented correctly\n");
    if(errorDeckDisCount)
      printf("ERROR: Deck + Discard count is incorrect\n");
    printf("Pre-HandCount: %d   Post-HandCount %d\n", pre.handCount[p], post->handCount[p]);
    printf("Pre-Deck+Discard: %d   Post-Deck+Discard %d\n", pre.deckCount[p]+pre.discardCount[p], post->discardCount[p]+post->deckCount[p]);
    printf("Pre-Discard+Deck Treasure: %d\n", discardTreasure+deckTreasure);
    printf("Last card in hand: %d", last);
    printf("Second to Last card in hand: %d\n",scndToLast);
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
    //Randomize hand, deck, and discard
    for (i = 0; i < MAX_HAND; i++) {
      if (i < G.handCount[p]) {
        G.hand[p][i] = rand() % 17;
      }
      else {
        G.hand[p][i] = -1;
      }
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
    //check players hand for CARD, if not there the put it in hand
    for (i = 0; i < G.handCount[p]; i++) {
      if (G.hand[p][i] == CARD) {
        handPos = i;
        i = G.handCount[p];
      }
    }//put CARD into players hand if not there
    if (handPos == -1) { 
      handPos = rand() % G.handCount[G.whoseTurn];
      G.hand[p][handPos] = CARD;
    }

    checkAdventurer(CARD, &G, p, handPos);
  }

  return 0;
}


