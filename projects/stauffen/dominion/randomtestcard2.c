//random tester for embargo card

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
	int randInt, choice, handPos;
	int numTests = 10;
	char *failedTests[numTests];  //each time a test fails, it's title will be put here
	kCards = kingdomCards(adventurer, feast, mine, smithy, baron, embargo, tribute, cutpurse, outpost, gardens); 	 //10 kingdom cards
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
				
		//manually place embargo in hand at random position
		randInt = (int)(Random()*1000)%5;
		G1->hand[G1->whoseTurn][randInt] = embargo;
		handPos = randInt;
		
		//copy first gameState to second
		*G2 = *G1;
		
		//TEST #1 - call cardEffect with embargo and a random card as choice 1. check overall success
		randInt = (int)(Random()*1000)%20 + 7;      			//enum 7-26
		while (G1->supplyCount[randInt] == -1 || randInt == 22){	//if card is embargo or not in play...
			randInt = (int)(Random()*1000)%20 + 7;
		}
		choice = randInt;
		result = cardEffect(embargo, choice, 0, 0, G1, handPos, bonus);
		printf("TESTING CARDEFFECT (EMBARGO) SUCCESS... "); assertResult = intAssert(result, 0);
		failures += assertResult;         //if test failed, assertResult is 1 and adds 1 to "failures"
		if (assertResult == 1){
			pushString(failedTests, numTests, "cardEffect did not return success\n");
		}
		
		//TEST #2 - does "choice" pile have embargo token set?
		printf("TESTING EMBARGO TOKEN... ");
		assertResult = intAssert(G1->embargoTokens[choice], 1);
		failures += assertResult;
		if (assertResult == 1){
			pushString(failedTests, numTests, "cardEffect: embargo token not set\n");
		}
		
		
		//TEST #3 - are any other embargo tokens set?
		printf("TESTING REST OF SUPPLY PILES... ");
		mistakes = 0;
		for (i=adventurer; i<treasure_map; i++){
			if (i != choice && G1->embargoTokens[i] == 1){     //any other pile affected is a mistake
				mistakes++;
			}
		}
		assertResult = intAssert(mistakes, 0);
		failures += assertResult;
		if (assertResult == 1){
			pushString(failedTests, numTests, "cardEffect: incorrect embargo token set\n");
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

		//TEST #6 - call playEmbargo and check overall success
		result = playEmbargo(G1->whoseTurn, G1, choice, handPos); 
		printf("TESTING PLAYEMBARGO SUCCESS... "); assertResult = intAssert(result, 0);
		failures += assertResult;
		if (assertResult == 1){
			pushString(failedTests, numTests, "playEmbargo did not return success\n");
		}
		
		//TEST #7 - does "choice" pile have embargo token set?
		printf("TESTING EMBARGO TOKEN... ");
		assertResult = intAssert(G1->embargoTokens[choice], 1);
		failures += assertResult;
		if (assertResult == 1){
			pushString(failedTests, numTests, "playEmbargo: embargo token not set\n");
		}

		//TEST #8 - are any other embargo tokens set?
		printf("TESTING REST OF SUPPLY PILES... ");
		mistakes = 0;
		for (i=adventurer; i<treasure_map; i++){
			if (i != choice && G1->embargoTokens[i] == 1){     //any other pile affected is a mistake
				mistakes++;
			}
		}
		assertResult = intAssert(mistakes, 0);
		failures += assertResult;
		if (assertResult == 1){
			pushString(failedTests, numTests, "playEmbargo: incorrect embargo token set\n");
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
			pushString(failedTests, numTests, "playEmbargo: kingdom card supplies affected\n");
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
			pushString(failedTests, numTests, "playEmbargo: victory card supplies affected\n");
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
