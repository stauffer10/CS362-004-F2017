//test helper functions
#include "testHelpers.h"
#include "dominion.h"
#include <stdio.h>

//makeshift assert function for int
//and providing extra print statements
//as an added test meausre, returns 0 if test passed, 1 otherwise
void intAssert(int received, int expected){
	
	if (received == expected){ 
		printf("TEST PASSED\n");
		return 0;
	}

	else{
		printf("TEST FAILED: EXPECTED %d, RECEIVED %d\n", expected, received);
		return 1;
	}

}


//function to compare kingdom card supply counts
void compareKC(struct gameState *G1, struct gameState *G2){

 	int i;
	int mistakes = 0;

	//kingdom cards are enum 7-26
	for (i=adventurer; i<=treasure_map; i++){
		if (G1->supplyCount[i] != G2->supplyCount[i]){
			mistakes++;
		}		
	}

	if (mistakes == 0){
		printf("SUPPLY COUNTS EQUAL: TEST PASSED\n");
	}	
	else{
		printf("TEST FAILED: %d SUPPLY COUNTS DIFFERENT\n", mistakes);
	}
}


//function to compare each victory card supply count
void compareVC(struct gameState *G1, struct gameState *G2){

	int i;
	int mistakes = 0;

	for (i=estate; i<=province; i++){
		if (G1->supplyCount[i] != G2->supplyCount[i]){
			mistakes++;
		}		
	}

	if (mistakes == 0){
		printf("SUPPLY COUNTS EQUAL: TEST PASSED\n");
	}	
	else{
		printf("TEST FAILED: %d SUPPLY COUNTS DIFFERENT\n", mistakes);
	}
}


//function to compare entire deck states for a specific player
void comparePlayerDeckStates(int player, struct gameState *G1, struct gameState *G2){
	

	int mistakes, i;

	//compare handCount, deckCount, discardCount, and playedCardCount
	//exit if failed so we don't have to waste time checking through each pile
	if (G1->handCount[player] != G2->handCount[player]){
		printf("GAMESTATE COMPARISON FAILED\n");
		return;
	}

	if (G1->deckCount[player] != G2->deckCount[player]){
		printf("GAMESTATE COMPARISON FAILED\n");
		return;
	}

	
	if (G1->discardCount[player] != G2->discardCount[player]){
		printf("GAMESTATE COMPARISON FAILED\n");
		return;
	}	

	

	
	//compare each card in hand
	for (i=0; i<G1->handCount[player]; i++){
		if (G1->hand[player][i] != G2->hand[player][i]){
			mistakes++;
		}
	}	
	
	if (mistakes != 0){
		printf("GAMESTATE COMPARISON FAILED\n");
		return;
	}

	//compare each card in deck
	for (i=0; i<G1->deckCount[player]; i++){
		if (G1->deck[player][i] != G2->deck[player][i]){
			mistakes++;
		}
	}	
	
	if (mistakes != 0){
		printf("GAMESTATE COMPARISON FAILED\n");
		return;
	}

	//compare each card in discard
	for (i=0; i<G1->discardCount[player]; i++){
		if (G1->discard[player][i] != G2->discard[player][i]){
			mistakes++;
		}
	}	
	
	if (mistakes != 0){
		printf("GAMESTATE COMPARISON FAILED\n");
		return;
	}
		
	if (mistakes != 0){
		printf("GAMESTATE COMPARISON FAILED\n");
		return;
	}

	printf("GAMESTATES EQUAL: TEST PASSED\n");			
}

//function for use in random tester. Randomizes all universal attributes of a game state
void randomizeGameState(int numberOfPlayers, int kCards[10], struct gameState *G1){
	
	//randomize whoseTurn
	randInt = (int)(Random()*1000)%numberOfPlayers;
	G1->whoseTurn = randomInt;
	
	//build hand
	G1->handCount[G1->whoseTurn] = 5;
	for (i=0; i<G1->handCount[G1->whoseTurn]; i++){
		
		randInt = (int)(Random()*1000)%17;     //17 options - 10 kCards, 3 treasure, 3 victory, curse
		
		if (randomInt < 10){
			G1->hand[G1->whoseTurn][i] = kCards[randomInt];
		}
		else if (randomInt == 10){
			G1->hand[G1->whoseTurn][i] = estate;
		}
		else if (randomInt == 11){
			G1->hand[G1->whoseTurn][i] = duchy;	
		}
		else if (randomInt == 12){
			G1->hand[G1->whoseTurn][i] = province;
		}
		else if (randomInt == 13){
			G1->hand[G1->whoseTurn][i] = copper;
		}
		else if (randomInt == 14){
			G1->hand[G1->whoseTurn][i] = silver;	
		}
		else if (randomInt == 15){
			G1->hand[G1->whoseTurn][i] = gold;
		}
		else{
			G1->hand[G1->whoseTurn][i] = curse;	
		}
	}
	
	//randomize player deck and discard
	G1->deckCount[G1->whoseTurn] = (int)(Random()*1000)%MAX_DECK;
	for (i=0; i<G1->deckCount[G1->whoseTurn]; i++){
		
		randInt = (int)(Random()*1000)%17;     //17 options - 10 kCards, 3 treasure, 3 victory, curse
		
		if (randomInt < 10){
			G1->deck[G1->whoseTurn][i] = kCards[randomInt];
		}
		else if (randomInt == 10){
			G1->deck[G1->whoseTurn][i] = estate;
		}
		else if (randomInt == 11){
			G1->deck[G1->whoseTurn][i] = duchy;
		}
		else if (randomInt == 12){
			G1->deck[G1->whoseTurn][i] = province;
		}
		else if (randomInt == 13){
			G1->deck[G1->whoseTurn][i] = copper;
		}
		else if (randomInt == 14){
			G1->deck[G1->whoseTurn][i] = silver;
		}
		else if (randomInt == 15){
			G1->deck[G1->whoseTurn][i] = gold;
		}
		else{
			G1->deck[G1->whoseTurn][i] = curse;
		}
	}
		
	G1->discardCount[G1->whoseTurn] = (int)(Random()*1000)%MAX_DECK;
	for (i=0; i<G1->discardCount[G1->whoseTurn]; i++){
		
		randInt = (int)(Random()*1000)%17;     //17 options - 10 kCards, 3 treasure, 3 victory, curse
		
		if (randomInt < 10){
			G1->discard[G1->whoseTurn][i] = kCards[randomInt];
		}
		else if (randomInt == 10){
			G1->discard[G1->whoseTurn][i] = estate;
		}
		else if (randomInt == 11){
			G1->discard[G1->whoseTurn][i] = duchy;
		}
		else if (randomInt == 12){
			G1->discard[G1->whoseTurn][i] = province;
		}
		else if (randomInt == 13){
			G1->discard[G1->whoseTurn][i] = copper;
		}
		else if (randomInt == 14){
			G1->discard[G1->whoseTurn][i] = silver;
		}
		else if (randomInt == 15){
			G1->discard[G1->whoseTurn][i] = gold;
		}
		else{
			G1->discard[G1->whoseTurn][i] = curse;
		}
	}	
	
	//randomize supply counts for each kingdom card
	for (i=0; i<10; i++){
		if (kCards[i] == great_hall || kCards[i] == gardens){
			G1->supplyCount[kCards[i]] = (int)(Random()*1000)%8;
		}
		else {
			G1->supplyCount[kCards[i]] = (int)(Random()*1000)%10;
		}
	}
	
	//randomize supply for curse, victory, and treasure cards
	if (numberOfPlayers == 2){
		G1->supplyCount[curse] = (int)(Random()*1000)%10;
		G1->supplyCount[estate] = (int)(Random()*1000)%8;
		G1->supplyCount[duchy] = (int)(Random()*1000)%8;
		G1->supplyCount[province] = (int)(Random()*1000)%8;
	}
	else if (numberOfPlayers == 3){
		G1->supplyCount[curse] = (int)(Random()*1000)%20;
		G1->supplyCount[estate] = (int)(Random()*1000)%12;
		G1->supplyCount[duchy] = (int)(Random()*1000)%12;
		G1->supplyCount[province] = (int)(Random()*1000)%12;
	}
	else {
		G1->supplyCount[curse] = (int)(Random()*1000)%30;
		G1->supplyCount[estate] = (int)(Random()*1000)%12;
		G1->supplyCount[duchy] = (int)(Random()*1000)%12;
		G1->supplyCount[province] = (int)(Random()*1000)%12;
	}
	j = 60 - (7 * numPlayers);   //number of copper cards in supply
	G1->supplyCount[copper] = (int)(Random()*1000)%j;
	G1->supplyCount[silver] = (int)(Random()*1000)%40;
	G1->supplyCount[gold] = (int)(Random()*1000)%30;
		
}
