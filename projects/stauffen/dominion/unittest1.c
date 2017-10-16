//unittest1 - tests the initializeGame function of dominion.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testHelpers.h"


int main(){

	int result, seed = 42;
	struct gameState *G;
	int i, numberOfPlayers, 
	int *kCards;

	//set up attributes for a game
	kCards = kingdomCards(8, 10, 12, 14, 16, 18, 20, 22, 24, 26); 	 //10 kingdom cards
	G = newGame();							//game state
	numberOfPlayers = 2;						//numPlayers
	
	//call initializeGame
		



	return 0;
}