//cardtest1 - tests the playAdventurer function of dominion.c

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
	G2 = newGame();							//game states
	numberOfPlayers = 3;						//legal numPlayers
	
	//initialize 3 player game with adventurer
	result = initializeGame(numberOfPlayers, kCards, seed, G1);

	//manually edit gameState so that player 1 has adventurer, 2 estates, and 2 copper in hand
	G1->hand[0][0] = adventurer;
	G1->hand[0][1] = estate;
	G1->hand[0][2] = estate;
	G1->hand[0][3] = copper;
	G1->hand[0][4] = copper;	

	//copy first gameState to second
	*G2 = *G1;

	//call cardEffect with adventurer and check overall success
	result = cardEffect(adventurer, 0, 0, 0, G1, 0, bonus);
	printf("USING CARDEFFECT FUNCTION (ADVENTURER)... \n");
	printf("TESTING FUNCTION SUCCESS... "); intAssert(result, 0);

	//does player's hand have 4 copper cards and total hand count of 7?
	printf("TESTING HANDCOUNT... ");
	intAssert(G1->handCount[0], G2->handCount[0] + 2);
	printf("TESTING HAND FOR 4 COPPER... ");
	j=0; //count variable
	for (i=0; i<G1->handCount[0]; i++){
		if (G1->hand[0][i] == copper){
			j++;
		}
	}
	intAssert(j, 4);

	//are other players' gameStates changed (they shouldn't be)?
	printf("TESTING OPPONENT DECK STATES...\n");
	comparePlayerDeckStates(1, G1, G2);
	comparePlayerDeckStates(2, G1, G2);

	//are kingdom and victory card piles affected (they shouldn't be)?
	printf("TESTING KINGDOM CARD COUNTS... ");
	compareKC(G1, G2);
	printf("TESTING VICTORY CARD COUNTS... ");
	compareVC(G1, G2);

	//reset gameState by copying from second
	*G1 = *G2;

	//call playAdventurer and check overall success
	printf("USING PLAYADVENTURER FUNCTION...\n");
	result = playAdventurer(0, G1); 
	printf("TESTING OVERALL SUCCESS... "); intAssert(result, 0);

	//does player's hand have 4 copper cards and total hand count of 7?
	printf("TESTING HANDCOUNT... ");
	intAssert(G1->handCount[0], G2->handCount[0] + 2);
	printf("TESTING HAND FOR 4 COPPER... ");
	j=0; //count variable
	for (i=0; i<G1->handCount[0]; i++){
		if (G1->hand[0][i] == copper){
			j++;
		}
	}
	intAssert(j, 4);

	//are other players' gameStates changed (they shouldn't be)?
	printf("TESTING OPPONENT DECK STATES...\n");
	comparePlayerDeckStates(1, G1, G2);
	comparePlayerDeckStates(2, G1, G2);

	//are kingdom and victory card piles affected (they shouldn't be)?
	printf("TESTING KINGDOM CARD COUNTS... ");
	compareKC(G1, G2);
	printf("TESTING VICTORY CARD COUNTS... ");
	compareVC(G1, G2);




	return 0;
}
