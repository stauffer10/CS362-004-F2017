//test helper functions

//makeshift assert function for int
//and providing extra print statements
void intAssert(int a, int b){
	
	if (a == b){ 
		printf("TEST PASSED\n");
	}

	else{
		printf("TEST FAILED: EXPECTED %d, RECEIVED %d\n", a, b);
	}
}


//function to compare kingdom card supply counts
void compareKC(struct gameState *G1, struct gameState *G2){

 	int i;
	int mistakes = 0;

	//kingdom cards are enum 8-27
	for (i=8; i<=27; i++){
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