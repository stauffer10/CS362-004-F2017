//unittest3 - tests the endTurn function of dominion.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testHelpers.h"
#include <stdio.h>


int main(){

	int result, seed = 25;
	struct gameState *G1;
	struct gameState *G2;
	int i, j, numberOfPlayers; 
	int *kCards;

	//set up attributes for a game
	kCards = kingdomCards(adventurer, feast, mine, smithy, baron, minion, tribute, cutpurse, outpost, gardens); 	 //10 kingdom cards
	G1 = newGame();	
	G2 = newGame();							//game states
	numberOfPlayers = 2;						//legal numPlayers
	
	//call initializeGame
	result = initializeGame(numberOfPlayers, kCards, seed, G1);

	//copy first gameState to second
	*G2 = *G1;

	//call endTurn
	result = endTurn(G1);

	//check overall success or failure
	printf("TESTING FUNCTION SUCCESS... "); intAssert(result, 0);

	//did whoseTurn increase for G1?
	printf("TESTING WHOSETURN... "); intAssert(G1->whoseTurn, G2->whoseTurn + 1);
	
	//is player 1's hand empty?
	printf("TESTING PLAYER 1 HAND COUNT... "); intAssert(G1->handCount[0], 0);

	//is player 1's discard 5?
	printf("TESTING PLAYER 1 DISCARD COUNT... "); intAssert(G1->discardCount[0], 5);

	//are numBuys and numActions reset to 1?
	printf("TESTING TURN ATTRIBUTES... \n");
	printf("NUMBUYS: "); intAssert(G1->numBuys, 1);
	printf("NUMACTIONS: "); intAssert(G1->numActions, 1);
	printf("OUTPOSTPLAYED: "); intAssert(G1->outpostPlayed, 0);

	//call endTurn again
	result = endTurn(G1);

	//did whoseTurn reset to player 1?
	printf("TESTING WHOSETURN... "); intAssert(G1->whoseTurn, 0);
	
	//is player 2's hand empty?
	printf("TESTING PLAYER 2 HAND COUNT... "); intAssert(G1->handCount[1], 0);

	//is player 2's discard 5?
	printf("TESTING PLAYER 2 DISCARD COUNT... "); intAssert(G1->discardCount[1], 5);
	
	//set 3 kingdom card piles to 0 (game over)
	G1->supplyCount[feast] = 0;
	G1->supplyCount[baron] = 0;
	G1->supplyCount[tribute] = 0;
	
	//call endTurn
	result = endTurn(G1);

	//did whoseTurn advance to player 2 (it shouldn't according to dominion.h)?
	printf("TESTING END OF GAME BEHAVIOR... "); intAssert(G1->whoseTurn, 0);


	return 0;
}
