//unittest1 - tests the initializeGame function of dominion.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testHelpers.h"
#include <stdio>


int main(){

	int result, seed = 42;
	struct gameState *G;
	int i, j, numberOfPlayers, badNumPlayers, copperCount, estateCount; 
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
`	printf("TESTING KINGDOM CARD SUPPLY COUNTS...\n");
	for (i=adventurer; i<treasure_map; i++){
		printf("Kcard #%d: ", i);
		
		//test against expected outcomes
		if (i==adventurer || i==feast || i==mine || i==smithy || i==baron || i==minion ||
		    i==tribute || i==cutpurse || i==outpost){
			intAssert(G->supplyCount[i], 10);
		}
		else if (i==gardens){
			intAssert(G->supplyCount[i], 8);
		}
		else{
			intAssert(G->supplyCount[i], -1);
		}

	}

	//Are victory, treasure, and curse card piles correct?
	printf("TESTING CURSE CARD SUPPLY COUNT...\n");
	printf("CURSE: "); intAssert(G->supplyCount[curse], 10);
	printf("TESTING VICTORY CARD SUPPLY COUNTS...\n");
	printf("ESTATE: "); intAssert(G->supplyCount[estate], 8);
	printf("DUCHY: "); intAssert(G->supplyCount[duchy], 8);
	printf("PROVINCE: "); intAssert(G->supplyCount[province], 8);
	printf("TESTING TREASURE CARD SUPPLY COUNTS...\n");
	printf("COPPER: "); intAssert(G->supplyCount[copper], 46);
	printf("SILVER: "); intAssert(G->supplyCount[silver], 40);
	printf("GOLD: "); intAssert(G->supplyCount[gold], 30);
	
	//Are player decks correct?
	printf("TESTING PLAYER DECKS...\n");
	copperCount = 0;
	estateCount = 0;

	for (i=1; i<3; i++){
		printf("PLAYER %d: \n", i);
		for (j=0; j<10; j++){
			if (G->deck[i][j] == copper){
				copperCount++;
			}
			else if (G->deck[i][j] == estate){
				estateCount++;
			}
		}
		printf("7 COPPER: "); intAssert(copperCount, 7);
		printf("3 ESTATES: "); intAssert(estateCount, 3); 		
	}


	//Are embargo tokens for each pile at 0?
	j = 0;    //keep count of embargo tokens
	for (i=adventurer; i<treasure_map; i++){
		if (G->embargoTokens[i] == 1){
			j++;
		}
	}
	printf("TESTING EMBARGO TOKENS... ");
	intAssert(j, 0);


	//Are player 1's gameState attributes correct for first turn?
	printf("TESTING FIRST TURN ATTRIBUTES... \n");
	printf("NUMBUYS: "); intAssert(G->numBuys, 1);
	printf("NUMACTIONS: "); intAssert(G->numActions, 1);
	printf("WHOSETURN: "); intAssert(G->whoseTurn, 1);
	printf("OUTPOSTPLAYED: "); intAssert(G->outpostPlayed, 0);


	//Does initializeGame fail with bad kingdom card input?
	printf("TESTING FUNCTION WITH BAD KCARD INPUT... ");
	result = initializeGame(numberOfPlayers, badKCards, seed, G);
	intAssert(result, 1);


	//Does initializeGame fail with bad number of players?
	printf("TESTING FUNCTION WITH BAD NUM PLAYER INPUT... ");
	result = initializeGame(badNumPlayers, kCards, seed, G);
	intAssert(result, 1);


	return 0;
}