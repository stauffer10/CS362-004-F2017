//cardtest3 - tests the playEmbargo function of dominion.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testHelpers.h"
#include <stdio.h>


int main(){

	int result, seed = 50;
	struct gameState *G1; 
	struct gameState *G2;
	int i, j, numberOfPlayers; 
	int *kCards;
	int *bonus = &seed;  //generic int pointer to use as necessary function parameter

	//set up attributes for a game
	kCards = kingdomCards(adventurer, feast, mine, smithy, baron, minion, tribute, cutpurse, outpost, embargo); 	 //10 kingdom cards
	G1 = newGame();
	G2 = newGame();							//game states
	numberOfPlayers = 3;						//legal numPlayers

	//initialize 3 player game with embargo and adventurer but not sea hag
	result = initializeGame(numberOfPlayers, kCards, seed, G1);

	//manually put smithy in hand
	G1->hand[0][0] = embargo;
	G1->hand[0][1] = estate;
	G1->hand[0][2] = estate;
	G1->hand[0][3] = copper;
	G1->hand[0][4] = copper;	

	//copy first gameState to second
	*G2 = *G1;

	//call cardEffect with embargo and adventurer as choice 1 and check overall success
	result = cardEffect(embargo, adventurer, 0, 0, G1, 0, bonus);
	printf("USING CARDEFFECT FUNCTION (EMBARGO)... \n");
	printf("TESTING FUNCTION SUCCESS... "); intAssert(result, 0);

	//does adventurer pile have embargo token set to 1?
	printf("TESTING ADVENTURER PILE FOR EMBARGO TOKEN... ");
	intAssert(G1->embargoTokens[adventurer], 1);

	//are other players' gameStates changed (they shouldn't be)?
	printf("TESTING OPPONENT DECK STATES...\n");
	comparePlayerDeckStates(1, G1, G2);
	comparePlayerDeckStates(2, G1, G2);

	//are kingdom and victory card counts affected (they shouldn't be)?
	printf("TESTING KINGDOM CARD COUNTS... ");
	compareKC(G1, G2);
	printf("TESTING VICTORY CARD COUNTS... ");
	compareVC(G1, G2);

	//reset gameState by copying from second
	*G1 = *G2;

	//call playEmbargo with adventurer as choice 1 and check overall success
	printf("USING PLAYEMBARGO FUNCTION...\n");
	result = playEmbargo(0, G1, adventurer, 0); 
	printf("TESTING OVERALL SUCCESS... "); intAssert(result, 0);

	//does adventurer pile have embargo token set to 1?
	printf("TESTING ADVENTURER PILE FOR EMBARGO TOKEN... ");
	intAssert(G1->embargoTokens[adventurer], 1);

	//are other players' gameStates changed (they shouldn't be)?
	printf("TESTING OPPONENT DECK STATES...\n");
	comparePlayerDeckStates(1, G1, G2);
	comparePlayerDeckStates(2, G1, G2);

	//are kingdom and victory card counts affected (they shouldn't be)?
	printf("TESTING KINGDOM CARD COUNTS... ");
	compareKC(G1, G2);
	printf("TESTING VICTORY CARD COUNTS... ");
	compareVC(G1, G2);

	//reset gameState by copying from second
	*G1 = *G2;

	//call playEmbargo with sea hag as choice 1. Did it succeed? (it shouldn't)
	printf("TESTING FUNCTION WITH CARD NOT IN PLAY... ");
	result = playEmbargo(0, G1, sea_hag, 0); intAssert(result, -1);
		

	return 0;
}
