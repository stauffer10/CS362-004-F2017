//unittest2 - tests the fullDeckCount function of dominion.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testHelpers.h"
#include <stdio>


int main(){

	int result, seed = 42;
	struct gameState *G1, *G2;
	int i, j, numberOfPlayers, copperCount, estateCount; 
	int *kCards;

	//set up attributes for a game
	kCards = kingdomCards(adventurer, feast, mine, smithy, baron, minion, tribute, cutpurse, outpost, gardens); 	 //10 kingdom cards
	G1 = newGame();							//game state
	numberOfPlayers = 2;						//legal numPlayers
	
	//call initializeGame
	result = initializeGame(numberOfPlayers, kCards, seed, G);

	//copy second gameState from first
	memcpy(G2, G1, sizeOf(struct gameState));

	//call fullDeckCount for first player and verify it is 10
	count = fullDeckCount(1, c


	//add a smithy to deck, subtract 4 copper


	//call fullDeckCount for first player again


	//Is fullDeckCount 3 less than the last call?

	
	//Were any non-deck related attributes of gameState affected by call to fullDeckCount? 
	 

	return 0;
}