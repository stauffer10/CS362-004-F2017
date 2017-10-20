//unittest2 - tests the fullDeckCount function of dominion.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testHelpers.h"
#include <stdio.h>


int main(){

	int result, seed = 42;
	struct gameState *G;
	int i, j, numberOfPlayers, copperCount, estateCount; 
	int *kCards;

	//set up attributes for a game
	kCards = kingdomCards(adventurer, feast, mine, smithy, baron, minion, tribute, cutpurse, outpost, gardens); 	 //10 kingdom cards
	G = newGame();							//game state
	numberOfPlayers = 2;						//legal numPlayers
	
	//call initializeGame
	result = initializeGame(numberOfPlayers, kCards, seed, G);

	//call fullDeckCount for first player and verify it is 3 estates, 7 copper
	copperCount = fullDeckCount(0, copper, G);
	estateCount = fullDeckCount(0, estate, G);

	printf("TESTING FULLDECKCOUNT... \n");
	printf("COPPERS: "); intAssert(copperCount, 7);
	printf("ESTATES: "); intAssert(estateCount, 3);
	
	//Were any non-deck related attributes of gameState affected by call to fullDeckCount? 
	printf("TESTING FIRST TURN ATTRIBUTES... \n");
	printf("NUMBUYS: "); intAssert(G->numBuys, 1);
	printf("NUMACTIONS: "); intAssert(G->numActions, 1);
	printf("WHOSETURN: "); intAssert(G->whoseTurn, 0);
	printf("OUTPOSTPLAYED: "); intAssert(G->outpostPlayed, 0);
	 

	return 0;
}
