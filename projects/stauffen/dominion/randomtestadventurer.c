//randomtestadventurer.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testHelpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
	int randInt, handPos;
	int numTests = 10;
	char *failedTests[numTests];  //each time a test fails, it's title will be put here
	kCards = kingdomCards(adventurer, feast, mine, smithy, baron, minion, tribute, cutpurse, outpost, gardens); 	 //10 kingdom cards
	G1 = newGame();
	G2 = newGame();							//game states	
	int assertResult, mistakes, failures = 0;      //keeps track of failed tests for each iteration


	//within loop...
	for (loopIndex=0; loopIndex<50; loopIndex++){

		//clear failures
		failures = 0;
		
		//clear failed tests array
		for (i=0; i<numTests; i++){
			failedTests[i] = " ";
		}
		
		//randomize numPlayers (2-4) and seed for initializeGame()
		numberOfPlayers = (rand()%3) + 2;
		seed = rand()%1000;
		
		//initialize game
		result = initializeGame(numberOfPlayers, kCards, seed, G1);
		
		//separate function to randomize all features of gamestate
		randomizeGameState(numberOfPlayers, kCards, G1);
				
		//manually place adventurer in hand at random position
		randInt = (int)(Random()*1000)%5;
		G1->hand[G1->whoseTurn][randInt] = adventurer;
		handPos = randInt;
		
		//copy first gameState to second
		*G2 = *G1;
		
		//TEST #1 - call cardEffect with adventurer and check overall success
		result = cardEffect(adventurer, 0, 0, 0, G1, handPos, bonus);
		printf("TESTING CARDEFFECT (ADVENTURER) SUCCESS... "); assertResult = intAssert(result, 0);
		failures += assertResult;         //if test failed, assertResult is 1 and adds 1 to "failures"
		if (assertResult == 1){
			pushString(failedTests, numTests, "cardEffect did not return success\n");
		}
		
		//TEST #2 - does player have total handcount of 7?
		printf("TESTING HANDCOUNT... ");
		assertResult = intAssert(G1->handCount[G1->whoseTurn], G2->handCount[G1->whoseTurn] + 2);
		failures += assertResult;
		if (assertResult == 1){
			pushString(failedTests, numTests, "cardEffect: handcount not updated correctly\n");
		}
		
		//TEST #3 - does player's hand have +2 copper cards?
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
		if (assertResult == 1){
			pushString(failedTests, numTests, "cardEffect: incorrect copper count in hand\n");
		}

		
		//TEST #4 - are any kingdom card supply counts changed?
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
		if (assertResult == 1){
			pushString(failedTests, numTests, "cardEffect: kingdom card supplies affected\n");
		}
		
		//TEST #5 - are any victory card supply counts changed?
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
		if (assertResult == 1){
			pushString(failedTests, numTests, "cardEffect: victory card supplies affected\n");
		}
		
		//reset gameState by copying from second
		*G1 = *G2;

		//TEST #6 - call playAdventurer and check overall success
		result = playAdventurer(G1->whoseTurn, G1); 
		printf("TESTING PLAYADVENTURER SUCCESS... "); assertResult = intAssert(result, 0);
		failures += assertResult;
		if (assertResult == 1){
			pushString(failedTests, numTests, "playAdventurer did not return success\n");
		}
		
		//TEST #7 - does player have total handcount of 7?
		printf("TESTING HANDCOUNT... ");
		assertResult = intAssert(G1->handCount[G1->whoseTurn], G2->handCount[G1->whoseTurn] + 2);
		failures += assertResult;
		if (assertResult == 1){
			pushString(failedTests, numTests, "playAdventurer: hand count not updated correctly\n");
		}
		
		//TEST #8 - does player's hand have +2 copper cards?
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
		if (assertResult == 1){
			pushString(failedTests, numTests, "playAdventurer: incorrect copper count in hand\n");
		}
		
		//TEST #9 - are any kingdom card supply counts changed?
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
		if (assertResult == 1){
			pushString(failedTests, numTests, "playAdventurer: kingdom card supplies affected\n");
		}
		
		//TEST #10 - are any victory card supply counts changed?
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
		if (assertResult == 1){
			pushString(failedTests, numTests, "playAdventurer: victory card supplies affected\n");
		}
		
		//if failures > 0, report seed number and number of failures
		if (failures > 0){
			printf("********ITERATION %d: %d FAILURES USING SEED %d***********", loopIndex+1, failures, seed);
			
			//print all failed tests
			printf("FAILED TESTS:\n");
			for (i=0; i<numTests; i++){
				printf("%s", failedTests[i]);
			}
			printf("\n");
		}

	}
	
		
	return 0;
}
