/*******************************************************************************
* Author: David Bacher-Hicks
* Date:   5 November 2017
* Description: Random test generator for the smithy card
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "cmpGameState.h"
#include "dominion.h"
#include "testing.h"

const int SMITHY_D_CARDS = 3;
const int N_TESTS        = 1000;


/*
 * Check the post conditions given two game states, pre and post
 *  stores the results in the testSummary results pointer
 */
void checkPostConditions (struct gameState * state, struct gameState * preState, testSummary * results)
{
  int equalitySet = 
    GS_NOT_HAND_DECK_DISC & ~GS_NUM_ACTIONS_MASK & ~GS_PLAYED_CARDS_MASK & ~GS_COINS_MASK;

  int player = preState->whoseTurn;
  int preSummary[N_CARDS_IMPLEMENTED], 
      postSummary[N_CARDS_IMPLEMENTED];

  /* get a count of cards expected to be drawn */
  int dCards = preState->deckCount[player] + preState->discardCount[player] < SMITHY_D_CARDS ?
               preState->deckCount[player] + preState->discardCount[player] : SMITHY_D_CARDS;
  
  /* check that hand count was incremented and number of actions decremented */
  expect("hand count incremented... ", results,
    state->handCount[player] == preState->handCount[player] + dCards - 1);
  
  expect("numActions decremented... ", results, 
    preState->numActions - 1 == state->numActions);
  
  /* no cards created or destroyed... */
  summarizeCards(preSummary,  preState, PLAYER[player], HAND | DECK | DISCARD);
  summarizeCards(postSummary, state,    PLAYER[player], HAND | DECK | DISCARD);

  expect("combined pre- discards+hand+deck == post- discards+hand+deck... ", results,
    cmpArrays(preSummary, N_CARDS_IMPLEMENTED, postSummary, N_CARDS_IMPLEMENTED) == 0);


  /* check that smithy is discarded */
  summarizeCards(preSummary,  preState, PLAYER[player], DISCARD);
  summarizeCards(postSummary, state,    PLAYER[player], DISCARD);
  preSummary[smithy] += 1;
  expect("Smithy is discarded... ", results,
    cmpArrays(preSummary, N_CARDS_IMPLEMENTED, postSummary, N_CARDS_IMPLEMENTED) == 0);

  /* check elements expected to remain constant */
  testGameStateEquality(state, preState, equalitySet, results);
}


/*
 *  establish the game state and ensure the player has a smithy
 */
void setupGameState (struct gameState * state, struct gameState * preState, int * pos)
{
  /* generate a random game state */
  randomGameState(state);
  
  /* give the player a smithy */
  if (state->handCount[state->whoseTurn] > 0) {
    *pos = rand() % state->handCount[state->whoseTurn];
  } else {
    *pos = 0;
    state->handCount[state->whoseTurn] = 1;
  }
  state->hand[state->whoseTurn][*pos] = smithy;

  /* update the coins for the modded hand and find the expected card count change */
  updateCoins(state->whoseTurn, state, 0);

  /* setup done, copy pre-state */
  cpState(preState, state);
}


/*
 * run the tests
 */
int main ()
{
  srand(time(0));

  int i, smithyPos, returnValue;
  struct gameState state;
  struct gameState preState;
  testSummary results;
  int comparison[N_CARDS_IMPLEMENTED];

  for (i = 0; i < N_TESTS; i++) {
    /* get a random game state and run the card */
    setupGameState(&state, &preState, &smithyPos);
    returnValue = playCard(smithyPos, 0, 0, 0, &state);

    printf("==== Test %6d ====\n", i + 1);
    printf(" == Pre-State == \n"); 
    printGameState(&preState);
    printf(" == Post-State ==\n");
    printGameState(&state);

    printf(" == HAND | DECK change == \n"); 
    compareStates(comparison, &preState, &state, PLAYER[preState.whoseTurn], HAND | DECK);
    printSummary(comparison);

    /* ensure the card should have run, then check post conditions */ 
    if (preState.numActions ==  0) {
      expect("numActions == 0; expected failure... ", &results,
        returnValue == -1);
    } else if (preState.phase != 0) {
      expect("phase != 0; expected failure... ", &results,
        returnValue == -1);
    } else {
      expect("numActions > 0; expected success...", &results, 
        returnValue != -1);

      checkPostConditions(&state, &preState, &results);
    }
  }

  /* print a summary */
  printTestSummary(&results);
  return 0;
}
