//randomtestadventurer.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testHelpers.h"
#include <stdio.h>
#include <stdlib.h>

#define ITERATIONS	1000;

int main(){
	
	srand(10);     //seed rand() for pre-initializeGame randomization
					//using different random generator so as not to conflict with dominion randomness
	
	//declare variables
	int result, seed;
	struct gameState *G1; 
	struct gameState *G2;
	int loopIndex, i, j, k, numberOfPlayers; 
	int *kCards;
	int *bonus = &seed;  //generic int pointer to use as necessary function parameter
	int randInt;

	//set up attributes for a game
	kCards = kingdomCards(adventurer, feast, mine, smithy, baron, minion, tribute, cutpurse, outpost, gardens); 	 //10 kingdom cards
	G1 = newGame();
	G2 = newGame();							//game states
	int numberOfPlayers;	
	int assertResult, mistakes, failures = 0;      //keeps track of failed tests for each iteration


	//within loop...
	for (loopIndex=0; loopIndex<ITERATIONS; loopIndex++){
		
		//randomize numPlayers (2-4) and seed for initializeGame()
		numberOfPlayers = (rand()%3) + 2;
		seed = rand()%ITERATIONS;
		
		//initialize game
		result = initializeGame(numberOfPlayers, kCards, seed, G1);
		
		//separate function to randomize all features of gamestate
		randomizeGameState(numberOfPlayers, kCards, G1);
				
		//manually place adventurer in hand at random position
		randInt = (int)(Random()*1000)%5;
		G1->hand[G1->whoseTurn][randomInt] = adventurer;
		
		//copy first gameState to second
		*G2 = *G1;
		
		//call cardEffect with adventurer and check overall success
		result = cardEffect(adventurer, 0, 0, 0, G1, 0, bonus);
		printf("TESTING CARDEFFECT (ADVENTURER) SUCCESS... "); assertResult = intAssert(result, 0);
		failures += assertResult;         //if test failed, assertResult is 1 and adds 1 to "failures"
		
		//does player have total handcount of 7?
		printf("TESTING HANDCOUNT... ");
		assertResult = intAssert(G1->handCount[G1->whoseTurn], G2->handCount[G1->whoseTurn] + 2);
		failures += assertResult;
		
		//does player's hand have +2 copper cards?
		printf("TESTING HAND FOR +2 COPPER... ");
		j=0; //count variable
		for (i=0; i<G1->handCount[G1->whoseTurn]; i++){
			if (G1->hand[G1->whoseTurn][i] == copper){
				j++;
			}
		}
		k=0;
		for (i=0; i<G2->handCount[G1->whoseTurn]; i++){
			if (G2->hand[G1->whoseTurn][i] == copper){
				k++;
			}
		}
		assertResult = intAssert(j, k+2);
		failures += assertResult;
		
		//are any kingdom card supply counts changed?
		//kingdom cards are enum 7-26
		printf("TESTING KINGDOM CARD COUNTS... ");
		mistakes = 0;
		for (i=adventurer; i<=treasure_map; i++){
			if (G1->supplyCount[i] != G2->supplyCount[i]){
				mistakes++;
			}		
		}
		assertResult = intAssert(mistakes, 0);
		failures += assertResult;
		
		//are any victory card supply counts changed?
		//victory cards are enum 1,2,3
		printf("TESTING VICTORY CARD COUNTS... ");
		mistakes = 0;
		for (i=estate; i<=province; i++){
			if (G1->supplyCount[i] != G2->supplyCount[i]){
				mistakes++;
			}		
		}
		assertResult = intAssert(mistakes, 0);
		failures += assertResult;
		
		//reset gameState by copying from second
		*G1 = *G2;

		//call playAdventurer and check overall success
		result = playAdventurer(0, G1); 
		printf("TESTING PLAYADVENTURER SUCCESS... "); assertResult = intAssert(result, 0);
		failures += assertResult;
		
		//does player have total handcount of 7?
		printf("TESTING HANDCOUNT... ");
		assertResult = intAssert(G1->handCount[G1->whoseTurn], G2->handCount[G1->whoseTurn] + 2);
		failures += assertResult;
		
		//does player's hand have +2 copper cards?
		printf("TESTING HAND FOR +2 COPPER... ");
		j=0; //count variable
		for (i=0; i<G1->handCount[G1->whoseTurn]; i++){
			if (G1->hand[G1->whoseTurn][i] == copper){
				j++;
			}
		}
		k=0;
		for (i=0; i<G2->handCount[G1->whoseTurn]; i++){
			if (G2->hand[G1->whoseTurn][i] == copper){
				k++;
			}
		}
		assertResult = intAssert(j, k+2);
		failures += assertResult;
		
		//are any kingdom card supply counts changed?
		//kingdom cards are enum 7-26
		printf("TESTING KINGDOM CARD COUNTS... ");
		mistakes = 0;
		for (i=adventurer; i<=treasure_map; i++){
			if (G1->supplyCount[i] != G2->supplyCount[i]){
				mistakes++;
			}		
		}
		assertResult = intAssert(mistakes, 0);
		failures += assertResult;
		
		//are any victory card supply counts changed?
		//victory cards are enum 1,2,3
		printf("TESTING VICTORY CARD COUNTS... ");
		mistakes = 0;
		for (i=estate; i<=province; i++){
			if (G1->supplyCount[i] != G2->supplyCount[i]){
				mistakes++;
			}		
		}
		assertResult = intAssert(mistakes, 0);
		failures += assertResult;
		
		//if failures > 0, report seed number and number of failures
		if (failures > 0){
			printf("********ITERATION %d: %d FAILURES USING SEED %d***********", loopIndex+1, failures, seed);
		}
		
		//maybe have an array of test numbers and keep track of what failed?
	}
	
		
	return 0;
}
