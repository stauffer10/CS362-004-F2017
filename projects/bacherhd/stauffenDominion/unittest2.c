/*******************************************************************************
* name: David Bacher-Hicks
* date: 22 October 2017
* description: unit tests for the discard card function
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "testing.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "cmpGameState.h"

/* hands */
const int HAND_1[] = { };
const int HAND_2[] = { copper };
const int HAND_3[] = { smithy, silver, gold, estate, adventurer };
const int HAND_COUNT[] = { 0, 1, 5 };

const int EXP_RETURN[] = { -1, 0, 0 }; /* expected returns */
const int DISC_POS = 0;                /* discard position */

/* test name */
const char * TEST_NM[] = {
  "empty hand",
  "one copper",
  "full hand"
};


/*
 * post condition testing based on a pre and post gamestate.
 * params:  post    - the post game state
 *          pre     - the pre game state
 *          results - the test summary struct to use for tests
 *          flag    - trash flag value to test
 *          card    - card that should have been discarded 
 */
void testPostConditions(struct gameState * post, struct gameState * pre, testSummary * results, int flag, int card)
{
  /* define the elements expected to remain constant */
  unsigned int equalSet = GS_NOT_HAND_DECK_DISC | GS_DECK_MASK;
  
  /* develop card summaries */
  int preHand[N_CARDS_IMPLEMENTED];
  int preDiscard[N_CARDS_IMPLEMENTED];
  int postHand[N_CARDS_IMPLEMENTED];
  int postDiscard[N_CARDS_IMPLEMENTED];

  summarizeCards(preHand, pre, PLAYER[0], HAND);
  summarizeCards(preDiscard, pre, PLAYER[0], HAND);
  summarizeCards(postHand, post, PLAYER[0], HAND);
  summarizeCards(postDiscard, post, PLAYER[0], HAND);
  
  /* add the discarded hand to the post hand to align */
  postHand[card]++;
  
  /* if not trashed, remove the card from the post discard to align */
  if (!flag) {
    postDiscard[card]--;
  }
  
  /* expect the pre and post summaries to now be equal after alignment */
  expect("Discard contains card \t", results,
    cmpArrays(preDiscard, N_CARDS_IMPLEMENTED, postDiscard, N_CARDS_IMPLEMENTED) == 0);
  
  /* expected changes */
  expect("Discard count \t", results,
    post->discardCount[0] == pre->discardCount[0] + 1);
  
  expect("Card removed from hand\t", results,
    postHand[card] == preHand[card]);
  
  expect("Hand count decrement\t", results,
    post->handCount[0] == pre->handCount[0] - 1);
 
  /* expected constants */
  expect("Other cards unchanged\t", results,
    cmpArrays(preHand, N_CARDS_IMPLEMENTED, postHand, N_CARDS_IMPLEMENTED) == 0);

  testGameStateEquality(post, pre, equalSet, results);
}


int main ()
{
  struct gameState initialState; 
  struct gameState testState;
  struct gameState preState;

  /* jagged array of hands */ 
  const int * hands[] = { HAND_1, HAND_2, HAND_3 };
  int returnResult;
  
  testSummary results;

  if (initializeGame(N_PLAYERS, (int *) K_CARDS, SEED, &initialState) == -1) {
    fprintf(stderr, "Couldn't initialize game state\n");
    exit(1);
  }

  printf("###########################\n");
  printf("#### discardCard unit test ####\n");
  printf("###########################\n");

  
  /* loop through hands and trash flag combinations */
  int i, flag, card;
  for(i = 0; i < 3; i++) {
    for(flag = 0; flag < 2; flag++) {
      printf("\n === Test: %s, Flag=%d ===\n", TEST_NM[i], flag);
      
      /* restore the test state, copy in the test hand, backup the state */
      cpState(&testState, &initialState);
      memcpy(testState.hand[0], hands[i], sizeof(int) * HAND_COUNT[i]);
      testState.handCount[0] = HAND_COUNT[i];
      cpState(&preState, &testState);

      /* use discardCard */
      returnResult = discardCard(DISC_POS, 0, &testState, flag);
      
      /* test return value */
      expect("return value ", &results,
        returnResult == EXP_RETURN[i]);
      
      /* if success, then test post conditions */
      if (returnResult == EXP_RETURN[i]) {
        card = preState.hand[0][DISC_POS];
        testPostConditions(&testState, &preState, &results, flag, card);
      }
    }
  }
  
  /* print the test results */
  printTestSummary(&results);
  return 0;
}
