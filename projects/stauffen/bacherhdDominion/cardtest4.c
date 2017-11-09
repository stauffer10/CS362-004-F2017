//cardtest4 - tests the caSeaHag function of David's cardEffects.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testHelpers.h"
#include <stdio.h>


int main(){

	int result, seed = 19;
	struct gameState *G1; 
	struct gameState *G2;
	int i, j, numInDeck, numberOfPlayers; 
	int *kCards;
	int *bonus = &seed;  //generic int pointer to use as necessary function parameter

	//set up attributes for a game
	kCards = kingdomCards(adventurer, feast, mine, smithy, baron, minion, tribute, cutpurse, outpost, sea_hag); 	 //10 kingdom cards
	G1 = newGame();
	G2 = newGame();							//game states
	numberOfPlayers = 4;						//legal numPlayers

	//initialize 4 player game with sea hag
	result = initializeGame(numberOfPlayers, kCards, seed, G1);

	//manually put smithy in hand
	G1->hand[0][0] = sea_hag;
	G1->hand[0][1] = estate;
	G1->hand[0][2] = estate;
	G1->hand[0][3] = copper;
	G1->hand[0][4] = copper;	

	//copy first gameState to second
	*G2 = *G1;

	//call cardEffect with sea hag and check overall success
	result = cardEffect(sea_hag, 0, 0, 0, G1, 0, bonus);
	printf("USING CARDEFFECT FUNCTION (SEA_HAG)... \n");
	printf("TESTING FUNCTION SUCCESS... "); intAssert(result, 0);

	//do other 3 players have curse as first card in deck?
	//this is confirmed by checking the card at the highest position in each player's deck
	//also check that discard count is +1
	printf("TESTING EACH OPPONENT...\n");
	for (i=1; i<4; i++){
		printf("PLAYER &d HAS CURSE CARD... ", i+1);
		numInDeck = G1->deckCount[i];
		intAssert(G1->deck[i][numInDeck-1], curse);
		printf("PLAYER &d HAS +1 DISCARD... ", i+1);
		intAssert(G1->discardCount[i], G2->discardCount[i] + 1);
	}

	//is player 1's gameState affected (it shouldn't be)?
	comparePlayerDeckStates(0, G1, G2);

	//are kingdom and victory card counts affected (they shouldn't be)?
	printf("TESTING KINGDOM CARD COUNTS... ");
	compareKC(G1, G2);
	printf("TESTING VICTORY CARD COUNTS... ");
	compareVC(G1, G2);

	//reset gameState by copying from second
	*G1 = *G2;
	
	//call playSeaHag and check for overall success
	printf("USING CA_SEAHAG...\n");
	result = caSeaHag(G1, 0); 
	printf("TESTING FUNCTION SUCCESS... "); intAssert(result, 0);

	//do other 3 players have curse as first card in deck?
	//does every other player have +1 discard?
	printf("TESTING EACH OPPONENT...\n");
	for (i=1; i<4; i++){
		printf("PLAYER &d HAS CURSE CARD... ", i+1);
		numInDeck = G1->deckCount[i];
		intAssert(G1->deck[i][numInDeck-1], curse);
		printf("PLAYER &d HAS +1 DISCARD... ", i+1);
		intAssert(G1->discardCount[i], G2->discardCount[i] + 1);
	}


	//is player 1's gameState affected (it shouldn't be)?
	comparePlayerDeckStates(0, G1, G2);

	//are kingdom and victory card counts affected (they shouldn't be)?
	printf("TESTING KINGDOM CARD COUNTS... ");
	compareKC(G1, G2);
	printf("TESTING VICTORY CARD COUNTS... ");
	compareVC(G1, G2);


	return 0;
}
