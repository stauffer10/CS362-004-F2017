/*
 * cardtest1.c
 * Testing Village
 *
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main() {
    int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int p=0;
	struct gameState G, pre;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("*********************************\n*  Testing Card: %s\n*********************************\n", TESTCARD);

	// copy the game state to a test case
	G.hand[p][5]=village;
	G.handCount[p]++;

	memcpy(&pre, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &G, 5, &bonus);

	p = whoseTurn(&pre);

	if(pre.handCount[p]!= G.handCount[p])
		printf("Error: player hand count was not incremented correctly\n");

	if(G.hand[p][pre.handCount[p]-1]==-1)
		printf("Error: a card was not correctly added to the players hand\n");

	if(pre.playedCardCount+1!= G.playedCardCount)
		printf("Error: played card count not incremented correctly\n");

	if(G.playedCards[pre.playedCardCount] != village)
	{
		printf("Error: played card not added to played pile\n");
	}
	
	if( (pre.deckCount[p]+pre.discardCount[p]-1) != (G.deckCount[p]+G.discardCount[p]) )
		printf("Error: deck and or discard counts werent correctly decremented.\n");

	if(pre.numActions+2 != G.numActions)
		printf("Error: number of actions not correctly incremented.\n");

	return 0;
}
