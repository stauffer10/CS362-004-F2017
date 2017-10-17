//unittest4 - tests the gainCard function of dominion.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testHelpers.h"
#include <stdio>


int main(){

	//set attributes - including a makeshift supply count variable


	//initialize game that includes smithy but not adventurer


	//copy second gameState from first


	//call gainCard with smithy and toFlag=1, decrease supply count


	//check overall pass (return 0)


	//does gameState->smithyCount = supply count?


	//do victory cards remain unchanged?


	//are other gameState attributes (numBuys, numActions, whoseTurn, etc) unchanged?


	//are all other kingdom card piles unchanged?


	//are deck and deckCount increased by 1?


	//copy second gameState from first again


	//call gainCard with smithy and toFlag=2, decrease supply count


	//does gameState->smithyCount = supply count?


	//are hand and handCount increased by 1?


	//copy second gameState from first again


	//call gainCard with smithy and toFlag=3, decrease supply count


	//does gameState->smithyCount = supply count?


	//are discard and discardCount increased by 1?


	//try to call gainCard for adventurer


	//did call succeed (it shouldn't)?


	
	return 0;
}