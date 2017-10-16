//test helper functions

//makeshift assert function for int
//and providing extra print statements
int intAssert(int a, int b){
	
	if (a == b){ 
		printf("TEST PASSED\n");
	}

	else{
		printf("TEST FAILED: EXPECTED %d, RECEIVED %d\n", a, b);
		return 1;
	}

	return 0;
}


//function to compare kingdom card supply counts
void compareKC(struct gameState *G1, struct gameState *G2){

 	int i;
	int mistakes = 0;

	//kingdom cards are enum 7-26
	for (i=7; i<=26; i++){
		if (G1->supplyCount[i] != G2->supplyCount[i]){
			mistakes++
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

	//victory cards are enum 1-3
	for (i=1; i<=3; i++){
		if (G1->supplyCount[i] != G2->supplyCount[i]){
			mistakes++
		}		
	}

	if (mistakes == 0){
		printf("SUPPLY COUNTS EQUAL: TEST PASSED\n");
	}	
	else{
		printf("TEST FAILED: %d SUPPLY COUNTS DIFFERENT\n", mistakes);
	}
}


//function to compare entire gamestates for a specific player
//the only relevant attributes to test are the cards in the player's full deck
void comparePlayerGameStates(int player, struct gameState *G1, struct gameState *G2){
	

	int mistakes, i;

	//compare handCount, deckCount, discardCount, and playedCardCount
	//exit if failed so we don't have to waste time checking through each pile
	if (G1->handCount[player] != G2->handCount[player]){
		printf("GAMESTATE COMPARISON FAILED\n");
		exit;
	}

	if (G1->deckCount[player] != G2->deckCount[player]){
		printf("GAMESTATE COMPARISON FAILED\n");
		exit;
	}

	
	if (G1->discardCount[player] != G2->discardCount[player]){
		printf("GAMESTATE COMPARISON FAILED\n");
		exit;
	}	

	
	if (G1->playedCardCount[player] != G2->playedCardCount[player]){
		printf("GAMESTATE COMPARISON FAILED\n");
		exit;
	}

	
	//compare each card in hand
	for (i=0; i<G1->handCount[player]; i++){
		if (G1->hand[player][i] != G2->hand[player][i]){
			mistakes++;
		}
		
	if (mistakes != 0){
		printf("GAMESTATE COMPARISON FAILED\n");
		exit;
	}

	//compare each card in deck
	for (i=0; i<G1->deckCount[player]; i++){
		if (G1->deck[player][i] != G2->deck[player][i]){
			mistakes++;
		}
		
	if (mistakes != 0){
		printf("GAMESTATE COMPARISON FAILED\n");
		exit;
	}

	//compare each card in discard
	for (i=0; i<G1->discardCount[player]; i++){
		if (G1->discard[player][i] != G2->discard[player][i]){
			mistakes++;
		}
		
	if (mistakes != 0){
		printf("GAMESTATE COMPARISON FAILED\n");
		exit;
	}									

	//compare each card in playedCards
	for (i=0; i<G1->playedCardCount[player]; i++){
		if (G1->playedCards[player][i] != G2->playedCards[player][i]){
			mistakes++;
		}
		
	if (mistakes != 0){
		printf("GAMESTATE COMPARISON FAILED\n");
		exit;
	}

	printf("GAMESTATES EQUAL: TEST PASSED\n");			
}