/*******************************************************************************
* name: David Bacher-Hicks
* date: 22 October 2017
* description: unit tests for the buy card function
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "testing.h"
#include "dominion.h"
#include "cmpGameState.h"

/* parallel test and expected values */
const int EXP_RETURN[]= {-1, -1, -1,  0,  0,  0, 0          };
const int TEST_SUPP[] = {10, 10,  0, 10,  1, 10, 10         };
const int TEST_COIN[] = {20,  0, 20, 10, 10, 10, TEST_COST  };
const int TEST_BUYS[] = { 0, 10, 10, 10, 10,  1, 10         };
const int NUM_TESTS   = 7;

const char * TEST_NAME[] = {
  "0 buys -> return -1",
  "0 coins -> return -1",
  "0 supply -> return -1",
  "10 each -> return 0",
  "1 supply edge case",
  "1 buy edge case",
  "v coins edge case"
};


/*
 * post condition testing based on a pre and post gamestate.
 * params:  post    - the post game state
 *          pre     - the pre game state
 *          results - the test summary struct to use for tests
 */
void testPostConditions(struct gameState * post, struct gameState * pre, testSummary * results)
{
  /* define expected unchanged elements */
  unsigned int equalSet = GS_ALL & 
  ~GS_NUM_BUYS_MASK & ~GS_COINS_MASK & ~GS_SUPPLY_COUNT_MASK & 
  ~GS_PHASE_MASK & ~GS_DISCARD_MASK;

  int player = post->whoseTurn; 
  
  /* ensure the supply pile was decremented and the discard count was incremented */
  expect("supply decremented\t", results, 
    post->supplyCount[TEST_K_CARD] == pre->supplyCount[TEST_K_CARD] - 1);

  expect("discard count incremented\t", results,
    post->discardCount[player] = pre->discardCount[player] + 1);
 
  /* develop a summary of pre and post-discards */ 
  int preSummary[N_CARDS_IMPLEMENTED];
  int postSummary[N_CARDS_IMPLEMENTED];
  summarizeCards(preSummary,  pre,  PLAYER[player], DISCARD);
  summarizeCards(postSummary, post, PLAYER[player], DISCARD);
  
  /* add the test card to the pre summary to align for testing */
  preSummary[TEST_K_CARD]++;
  
  /* check that the discard summary is as expected */
  expect("discard = discard + {card}\t", results,
    cmpArrays(preSummary, N_CARDS_IMPLEMENTED, postSummary, N_CARDS_IMPLEMENTED) == 0);
  
  /* ensure coins reduced by the right amount and buys were reduced by 1 */
  expect("coins reduced by cost\t", results,
    post->coins == pre->coins - TEST_COST);
  
  expect("buys reduced by 1\t", results,
    post->numBuys == pre->numBuys - 1);
  
  /* check all other elements expected to remain unchanged */
  testGameStateEquality(post, pre, equalSet, results); 
}


int main ()
{
  struct gameState initialState;
  struct gameState testState;
  struct gameState preState;
  
  printf("###########################\n");
  printf("#### buyCard unit test ####\n");
  printf("###########################\n");

  if (initializeGame(N_PLAYERS, (int *) K_CARDS, SEED, &initialState) == -1) {
    fprintf(stderr, "Couldn't initialize game state\n");
    exit(1);
  }
  
  /* initialize test summary */
  testSummary results;
  results.tests = 0;
  results.fail = 0;
  results.pass = 0;

  cpState(&testState, &initialState);
  
  /* test an out of range supply value */
  expect("Testing supply index out of range (100) ", &results,
    buyCard(100, &testState) == -1);
  
  /* loop through the test cases */
  int i, buyReturnValue;
  for (i = 0; i < NUM_TESTS; i++) {
    printf(" === test parameter set %d, %s ===\n", i, TEST_NAME[i]);
    
    /* restore the test state, set the supply count, coins, and number of buys */
    cpState(&testState, &initialState);
    testState.supplyCount[TEST_K_CARD] = TEST_SUPP[i];
    testState.coins     = TEST_COIN[i];
    testState.numBuys   = TEST_BUYS[i];

    /* backup state and use buyCard() */
    cpState(&preState, &testState);
    buyReturnValue = buyCard(TEST_K_CARD, &testState);
    
    /* check expected return value. If success, then test post conditions */
    expect("function return value\t", &results, buyReturnValue == EXP_RETURN[i]);
    if (buyReturnValue == 0) {
      testPostConditions(&testState, &preState, &results);
    }

    printf("\n\n");
  }
  
  /* print test results */
  printTestSummary(&results);
  return 0;
}
