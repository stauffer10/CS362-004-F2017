//cardtest2 - tests the playSmithy function of dominion.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testHelpers.h"
#include <stdio.h>


int main(){

	
	int result, seed = 12;
	struct gameState *G1;
	struct gameState *G2;
	int i, j, numberOfPlayers; 
	int *kCards;
	int *bonus = &seed;  //generic int pointer to use as necessary function parameter

	//set up attributes for a game
	kCards = kingdomCards(adventurer, feast, mine, smithy, baron, minion, tribute, cutpurse, outpost, gardens); 	 //10 kingdom cards
	G1 = newGame();	
	G2 = newGame();						//game states
	numberOfPlayers = 2;						//legal numPlayers
	
	//initialize 2 player game with smithy
	result = initializeGame(numberOfPlayers, kCards, seed, G1);

	//manually put smithy in hand
	G1->hand[0][0] = smithy;
	G1->hand[0][1] = estate;
	G1->hand[0][2] = estate;
	G1->hand[0][3] = copper;
	G1->hand[0][4] = copper;	

	//copy first gameState to second
	*G2 = *G1;

	//call cardEffect with smithy and check overall success
	result = cardEffect(smithy, 0, 0, 0, G1, 0, bonus);
	printf("USING CARDEFFECT FUNCTION (SMITHY)... \n");
	printf("TESTING FUNCTION SUCCESS... "); intAssert(result, 0);

	//does player 1 handCount increase by 2? (+3 cards and -1 to discard smithy)
	printf("TESTING HANDCOUNT... ");
	intAssert(G1->handCount[0], G2->handCount[0] + 2);

	//does player 1 deckCount decrease by 3?
	printf("TESTING DECKCOUNT... ");
	intAssert(G1->deckCount[0], G2->deckCount[0] - 3);

	//are other players' gameStates changed (they shouldn't be)?
	printf("TESTING OPPONENT DECK STATES...\n");
	comparePlayerDeckStates(1, G1, G2);

	//are kingdom and victory card piles affected (they shouldn't be)?
	printf("TESTING KINGDOM CARD COUNTS... ");
	compareKC(G1, G2);
	printf("TESTING VICTORY CARD COUNTS... ");
	compareVC(G1, G2);

	//reset gameState by copying from second
	*G1 = *G2;

	//call playSmithy and check overall success
	printf("USING PLAYSMITHY FUNCTION...\n");
	result = playSmithy(0, G1, 0); 
	printf("TESTING OVERALL SUCCESS... "); intAssert(result, 0);

	//does player 1 handCount increase by 2? (+3 cards and -1 to discard smithy)
	printf("TESTING HANDCOUNT... ");
	intAssert(G1->handCount[0], G2->handCount[0] + 2);

	//does player 1 deckCount decrease by 3?
	printf("TESTING DECKCOUNT... ");
	intAssert(G1->deckCount[0], G2->deckCount[0] - 3);

	//are other players' gameStates changed (they shouldn't be)?
	printf("TESTING OPPONENT DECK STATES...\n");
	comparePlayerDeckStates(1, G1, G2);

	//are kingdom and victory card piles affected (they shouldn't be)?
	printf("TESTING KINGDOM CARD COUNTS... ");
	compareKC(G1, G2);
	printf("TESTING VICTORY CARD COUNTS... ");
	compareVC(G1, G2);
	


	return 0;
}
