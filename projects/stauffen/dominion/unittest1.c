//unittest1 - tests the initializeGame function of dominion.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testHelpers.h"
#include <stdio>


int main(){

	int result, seed = 42;
	struct gameState *G;
	int i, numberOfPlayers, badNumPlayers; 
	int *kCards;
	int *badKCards;    //initialized with duplicates - should fail

	//set up attributes for a game
	kCards = kingdomCards(adventurer, feast, mine, smithy, baron, minion, tribute, cutpurse, outpost, gardens); 	 //10 kingdom cards
	badKCards = kingdomCards(adventurer, adventurer, mine, smithy, baron, minion, tribute, cutpurse, outpost, sea_hag);   //10 kingdom cards with duplicate
	G = newGame();							//game state
	numberOfPlayers = 2;						//legal numPlayers
	badNumPlayers = 25;						//illegal numPlayers
	
	//call initializeGame
	result = initializeGame(numberOfPlayers, kCards, seed, G);


	//testing steps...
	
	//Did initializeGame execute without failing?
	printf("TESTING SUCCESSFUL SETUP OF GAME... ");
	intAssert(result, 0);

	//Was the number of players correctly initialized?
	printf("TESTING NUMBER OF PLAYERS... ");
	intAssert(G->numPlayers, numberOfPlayers);

	//Are all kingdom card supply counts correct? (10 for cards in play, 8 for gardens, -1 for others)


	//Are victory and treasure card piles correct?

	
	//Are player decks correct?


	//Are embargo tokens for each pile at 0?


	//Are player 1's gameState attributes correct for first turn?


	//Did initializeGame succeed overall (return 0)?


	//Does initializeGame fail with bad kingdom card input?


	//Does initializeGame fail with bad number of players?



	return 0;
}