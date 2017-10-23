/*******************************************************************************
* name: David Bacher-Hicks
* date: 22 October 2017
* description: unit tests for the adventurer card
*******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dominion.h"
#include "testing.h"
#include "cardEffects.h"
#include "cmpGameState.h"

/* a starting hand and an expected resulting hand from each of the test decks */
const int STARTING_HAND[5] = { copper, copper, copper, estate, estate };
const int EXPECTED_HAND[7] = { copper, copper, copper, estate, estate, gold, silver };
const int BAD_EXPECTED_HAND[8] = { copper, copper, copper, estate, estate, gold, silver, copper };

/* test decks with treasures in different locations */
const int TEST_DECK[3][8] = {
  { copper, silver, gold, great_hall, cutpurse, sea_hag, adventurer, smithy },
  { great_hall, cutpurse, sea_hag, adventurer, smithy, copper, silver, gold },
  { great_hall, copper, cutpurse, silver, sea_hag, gold, adventurer, smithy },
};

const int EXPECTED_DECK_1[] = { copper };
const int EXPECTED_DECK_2[] = { great_hall, cutpurse, sea_hag, adventurer, smithy, copper};
const int EXPECTED_DECK_3[] = { great_hall, copper, cutpurse };
const int EXPECTED_DECK_SIZE[] = { 1, 6, 3 };

/* 
 * expected discard piles, starting with an empty discard pile, to result from using the
 * adventurer card, which will discard all cards until two treasures have been drawn,
 * finally the adventurer card itself should be discarded
 */
const int EXPECTED_DISCARDS_1[] = { great_hall, cutpurse, sea_hag, adventurer, smithy, adventurer };
const int EXPECTED_DISCARDS_2[] = { adventurer };
const int EXPECTED_DISCARDS_3[] = { sea_hag, adventurer, smithy, adventurer };
const int EXPECTED_DISCARD_SIZE[] = { 6, 1, 4 };


int main ()
{
  struct gameState initialState;
  struct gameState testState;
  struct gameState preState;

  int i;
  
  if (initializeGame(N_PLAYERS, (int *) K_CARDS, SEED, &initialState) == -1) {
    fprintf(stderr, "Couldn't init game state\n");
    exit(1);
  }

  printf("###################################\n");
  printf("#### adventurer card unit test ####\n");
  printf("###################################\n");

  const int * expectedDiscards[3] = { EXPECTED_DISCARDS_1, EXPECTED_DISCARDS_2, EXPECTED_DISCARDS_3 };
  const int * expectedDecks[3]    = { EXPECTED_DECK_1, EXPECTED_DECK_2, EXPECTED_DECK_3 };

  /* test summary struct */
  testSummary results;
  results.tests = 0;
  results.pass = 0;
  results.fail = 0;

  /* loop through test decks and expected results */
  for (i = 0; i < 3; i++) {
    printf("\n\n=== TEST DECK %d ===\n", i);
    
    /* copy over original state, 
     *  copy the appropriate test deck and starting hand,
     *    then copy the original state to a backup 
     */
    cpState(&testState, &initialState);
    cpDeck(&testState, 0, (int *) TEST_DECK[i], 8);
    memcpy(testState.hand[0], STARTING_HAND, sizeof(STARTING_HAND));
    cpState(&preState, &testState);
    
    /* apply the adventurer to testState */
    int bonus = 0;
    cardEffect(adventurer, 0, 0, 0, &testState, 0, &bonus);
    
    /* run each individual test as a call to expect */
    printf("\n\n===== Testing Elements Expected to Change ===== \n");
    expect("testing player 0 hand size\t", &results, 
     testState.handCount[0] == preState.handCount[0] + 2);

    expect("testing player 0 hand cards\t", &results,
      memcmp(EXPECTED_HAND, testState.hand[0], 
        sizeof(*testState.hand[0]) * testState.handCount[0]) == 0);
    
    expect("testing player 0 deck size\t", &results,
      testState.deckCount[0] == preState.deckCount[0] - 2 - 
        (testState.discardCount[0] - preState.discardCount[0]));

    expect("testing player 0 deck cards\t", &results,
      memcmp(expectedDecks[i], testState.deck[0],
        sizeof(int) * EXPECTED_DECK_SIZE[i]) == 0);

    expect("testing player 0 discard size\t", &results,
      testState.discardCount[0] == EXPECTED_DISCARD_SIZE[i]);

    expect("testing player 0 discarded cards\t", &results,
      memcmp(expectedDiscards[i], testState.discard[0], 
        sizeof(*testState.discard[0]) * testState.discardCount[0]) == 0);
  
    printf("\n\n ===== Testing Elements Expected to Remain Constant ===== \n");
    testGameStateEquality(&testState, &preState, GS_NOT_HAND_DECK_DISC, &results);
  }

  printTestSummary(&results);
  return 0;
}
