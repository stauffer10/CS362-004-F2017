//unittest4 - tests the gainCard function of dominion.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testHelpers.h"
#include <stdio>


int main(){

	//set variables - including a makeshift supply count variable
	int result, seed = 100;
	struct gameState *G1, *G2;
	int i, j, numberOfPlayers; 
	int *kCards;
	int supplyCount = 10;

	//set up attributes for a game
	kCards = kingdomCards(smithy, steward, feast, mine, baron, minion, tribute, cutpurse, outpost, embargo); 	 //10 kingdom cards
	G1 = newGame();							//game state
	numberOfPlayers = 2;						//legal numPlayers
	
	//initialize game that includes smithy but not adventurer
	result = initializeGame(numberOfPlayers, kCards, seed, G1);

	//copy first gameState to second
	memcpy(G2, G1, sizeOf(struct gameState));

	//call gainCard for player 0 with smithy and toFlag=1, decrease supply count
	printf("GAINCARD TO DECK...\n");
	result = gainCard(smithy, G1, 1, 0);
	supplyCount--;

	//check overall pass (return 0)
	printf("TESTING FUNCTION SUCCESS... "); intAssert(result, 0);
	
	//does gameState->smithyCount = supply count?
	printf("TESTING SMITHY SUPPLY COUNT... "); intAssert(G1->supplyCount[smithy], supplyCount);

	//do victory cards remain unchanged?
	printf("TESTING VICTORY CARD PILES... \n");
	compareVC(G1, G2);

	//are other gameState attributes (numBuys, numActions, whoseTurn, etc) unchanged?
	printf("TESTING TURN ATTRIBUTES... \n");
	printf("NUMBUYS: "); intAssert(G1->numBuys, G2->numBuys);
	printf("NUMACTIONS: "); intAssert(G1->numActions, G2->numActions);
	printf("WHOSETURN: "); intAssert(G1->whoseTurn, G2->whoseTurn);
	printf("OUTPOSTPLAYED: "); intAssert(G1->outpostPlayed, G2->outpostPlayed);

	//are all other kingdom card piles unchanged?
	//smithy is first index of kCards so check 1-9
	printf("TESTING ALL OTHER KINGDOM CARD PILES...\n");
	for (i=1; i<10; i++){
		printf("kCard index %d: ");
		intAssert(G1->supplyCount[kCard[i]], 10);
	}

	//is deckCount increased by 1?
	printf("TESTING PLAYER DECK... \n");
	printf("DECKCOUNT: "); intAssert(G1->deckCount, G2->deckCount + 1);

	//copy second gameState from first again
	memcpy(G2, G1, sizeOf(struct gameState));

	//call gainCard with smithy and toFlag=2, decrease supply count
	printf("GAINCARD TO HAND...\n");	
	result = gainCard(smithy, G1, 2, 0);
	supplyCount--;

	//does gameState->smithyCount = supply count?
	printf("TESTING SMITHY SUPPLY COUNT... "); intAssert(G1->supplyCount[smithy], supplyCount);

	//is handCount increased by 1?
	printf("TESTING PLAYER HAND... \n");
	printf("HANDCOUNT: "); intAssert(G1->handCount, G2->handCount + 1);

	//copy second gameState from first again
	memcpy(G2, G1, sizeOf(struct gameState));

	//call gainCard with smithy and toFlag=3, decrease supply count
	printf("GAINCARD TO DISCARD...\n");	
	result = gainCard(smithy, G1, 3, 0);
	supplyCount--;

	//does gameState->smithyCount = supply count?
	printf("TESTING SMITHY SUPPLY COUNT... "); intAssert(G1->supplyCount[smithy], supplyCount);

	//is discardCount increased by 1?
	printf("TESTING PLAYER DISCARD... \n");
	printf("DISCARDCOUNT: "); intAssert(G1->discardCount, G2->discardCount + 1);


	//try to call gainCard for adventurer
	//did call succeed (it shouldn't)?
	printf("TESTING WITH CARD NOT IN GAME... ");
	result = gainCard(adventurer, G1, 1, 0); intAssert(result, 1);

	
	return 0;
}