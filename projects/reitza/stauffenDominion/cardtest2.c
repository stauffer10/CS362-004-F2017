/*
 * cardtest2.c
 * Testing Adventurer
 *
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
    int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int p=0;
	struct gameState G, pre;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	G.deck[p][G.deckCount[p]]= village;
	G.deckCount[p]++;
	G.supplyCount[village]--;
	printf("*********************************\n*  Testing Card: %s\n*********************************\n", TESTCARD);


	G.hand[p][5]=adventurer;
	G.handCount[p]++;
	int treasureCount=0;
	int c;

	for(c=0;c<G.discardCount[p];c++)
	{
		if(G.discard[p][c]==gold || G.discard[p][c]==silver || G.discard[p][c]==copper)
			treasureCount++;
	}
	for(c=0;c<G.deckCount[p];c++)
	{
		if(G.deck[p][c]==gold || G.deck[p][c]==silver || G.deck[p][c]==copper)
			treasureCount++;
	}
	if(treasureCount>2)
		treasureCount=2;
	

	// copy the game state to a test case
	memcpy(&pre, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &G, 5, &bonus);

	p = whoseTurn(&pre);
	
	//might want to go through deck and discard to confirm existence of 2 treasures.

	if(pre.handCount[p]+treasureCount!=G.handCount[p])
		printf("Error: hand count was not correctly incremented\n");

	for(c=0;c<treasureCount;c++)
	{
		if(G.hand[p][pre.handCount[p]+c]==-1)
			printf("Error: cards weren't correctly added to the players hand.\n");
	}

	if(G.playedCards[pre.playedCardCount] != adventurer)
	{
		printf("Error: played card not added to played pile\n");
	}

	if( (pre.deckCount[p]+pre.discardCount[p]-treasureCount) != (G.deckCount[p]+G.discardCount[p]) )
		printf("Error: deck and or discard counts werent correctly decremented.\n");

	return 0;
}
