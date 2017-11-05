/*******************************************************************************
* Author: David Bacher-Hicks
* Date:   5 November 2017
* Description: Random test generator for the smithy card
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "dominion_helpers.h"
#include "cmpGameState.h"
#include "dominion.h"
#include "testing.h"

const int N_TESTS = 1000;
const int N_ADV_TREASURES = 2;
const int N_DISCARDED = 1;

/*
 *  check each other player's cards to ensure they haven't changed
 */
void checkOthersCards (struct gameState * state, struct gameState * preState, testSummary * results)
{
  int i;
  for (i = 0; i < preState->numPlayers; i++) {
    if (i != preState->whoseTurn) {
      printf("Checking player %d\n", i);

      expect("Deck unchanged... ", results, 
        cmpArrays(state->deck[i], state->deckCount[i], preState->deck[i], preState->deckCount[i]) ==  0);

      expect("Hand unchanged... ", results,
        cmpArrays(state->hand[i], state->handCount[i], preState->hand[i], preState->handCount[i]) == 0);

      expect("Discards unchanged... ", results,
        cmpArrays(state->discard[i], state->discardCount[i], preState->discard[i], preState->discardCount[i]) == 0);
    } else {
      printf("Skipping active player, %d\n", i);
    }
  }
}


/*
 * Check the post conditions given two game states, pre and post
 *  stores the results in the testSummary results pointer
 */
void checkPostConditions (struct gameState * state, struct gameState * preState, testSummary * results)
{
  unsigned int equalitySet = GS_NOT_HAND_DECK_DISC & ~GS_COINS_MASK & ~GS_NUM_ACTIONS_MASK;  
  int preDeckDiscTreasures = totalTreasures(preState, preState->whoseTurn, DECK | DISCARD);
  int preHandTreasures = totalTreasures(preState, preState->whoseTurn, HAND);
  
  int postDeckDiscTreasures = totalTreasures(state, preState->whoseTurn, DECK | DISCARD);
  int postHandTreasures = totalTreasures(state, preState->whoseTurn, HAND);

  int dTreasures = preDeckDiscTreasures < N_ADV_TREASURES ?
                   preDeckDiscTreasures : N_ADV_TREASURES;
   
  printf("Hand Treasure:\n");
  printf("Pre\tPost\n");
  printf("%d\t%d\n", preHandTreasures, postHandTreasures);

  printf("Deck Treasure:\n");
  printf("Pre\tPost\n");
  printf("%d\t%d\n", preDeckDiscTreasures, postDeckDiscTreasures);
  
  printf("Expected dTresure = %d\n", dTreasures);
  
  /* ensure the hand size was incremented and deck decremented */
  expect("Hand size incremented... ", results,
    state->handCount[preState->whoseTurn] == preState->handCount[preState->whoseTurn] + dTreasures - N_DISCARDED);
   
  expect("Deck | Discard combined size decremented ", results,
    state->discardCount[preState->whoseTurn] + state->deckCount[preState->whoseTurn] == 
    preState->discardCount[preState->whoseTurn] + preState->deckCount[preState->whoseTurn] - dTreasures + N_DISCARDED);

  /* check change in treasure */
  expect("Deck | Discard treasures decremented... ", results,
    postDeckDiscTreasures == preDeckDiscTreasures - dTreasures);

  expect("Hand treasures incremented... ", results, 
    postHandTreasures == preHandTreasures + dTreasures);
  
  /* ensure no side effects to others cards and expected constant elements remain constant */
  checkOthersCards(state, preState, results);
  testGameStateEquality(state, preState, equalitySet, results); 
}


/*
 *  establish the game state and ensure the player has a smithy
 */
void setupGameState(struct gameState * state, struct gameState * preState, int * pos)
{
  /* generate random game state */
  randomGameState(state);
  
  /* give the player an adventurer card */
  if (state->handCount[state->whoseTurn] > 0) {
    *pos = rand() % state->handCount[state->whoseTurn];
  } else {
    *pos = 0;
    state->handCount[state->whoseTurn] = 1;
  }
  state->hand[state->whoseTurn][*pos] = adventurer;

  /* update coins in case the adventurer overwrote any coins */
  updateCoins(state->whoseTurn, state, 0);

  /* copy state */
  cpState(preState, state);
}


/*
 * Run the tests
 */
int main ()
{
  srand(time(0));

  struct gameState state;
  struct gameState preState;

  testSummary results;
  results.tests = 0;
  results.pass = 0;
  results.fail = 0;

  int advPos = 0;
  int returnValue = 0;
  int i;
  for (i = 0; i < N_TESTS; i++) {

    setupGameState(&state, &preState, &advPos);
    returnValue = playCard(advPos, 0, 0, 0, &state);

    printf("=== TEST %d ===\n", i + 1);
    printf(" == Pre-State ==\n");
    printGameState(&preState);
    printf(" == Post-State ==\n");
    printGameState(&state);
    
    if (preState.numActions == 0) {
      expect("No actions, expected failure... ", &results,
        returnValue == -1);
    } else if (preState.phase != 0) {
      expect("Wrong phase, expected failure... ", &results,
        returnValue == -1);
    } else {
      expect("Expected success... ", &results,
        returnValue == 0);

      checkPostConditions(&state, &preState, &results);
    }

  }

  printTestSummary(&results);
  return 0;
}
