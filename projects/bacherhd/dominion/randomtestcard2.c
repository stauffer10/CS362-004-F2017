/*******************************************************************************
* Author: David Bacher-Hicks
* Date:   5 November 2017
* Description: Random test generator for the sea hag card
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "cmpGameState.h"
#include "dominion.h"
#include "testing.h"

const int N_TESTS = 1000;

/*
 * Check the post conditions given two game states, pre and post
 *  stores the results in the testSummary results pointer
 */
void checkPostConditions (struct gameState * state, struct gameState * preState, testSummary * results)
{
  unsigned int equalitySet = GS_NOT_HAND_DECK_DISC & ~GS_SUPPLY_COUNT_MASK & ~GS_NUM_ACTIONS_MASK;

  int preCards[N_CARDS_IMPLEMENTED];
  int postCards[N_CARDS_IMPLEMENTED];
  int i, discardedDeckCard;
  
  /* check each player individually */
  for (i = 0; i < preState->numPlayers; i++) {
    printf("Checking player %d\n", i);
    if (i == preState->whoseTurn) {
      /* ensure the active player was not affected by the card */
      expect("Active player, expecting deck unchanged... ", results,
        cmpArrays(preState->deck[i], preState->deckCount[i], state->deck[i], state->deckCount[i]) == 0); 
    } else {
      /* ensure each other player was affected by the card */
      
      /* find the card that should have been discarded, on top of the player's deck */
      discardedDeckCard = preState->deck[i][preState->deckCount[i] - 1];
      
      /* summarize decks, pre and post */
      summarizeCards(preCards,  preState, PLAYER[i], DECK);
      summarizeCards(postCards, state,    PLAYER[i], DECK);
  
      /* modify based on expectations */
      preCards[curse]++;
      preCards[discardedDeckCard]--;
      
      expect("Top card is curse... ", results,
        state->deck[i][state->deckCount[i] - 1] == curse);

      expect("Top deck card discarded, curse gained... ", results,
        cmpArrays(preCards, N_CARDS_IMPLEMENTED, postCards, N_CARDS_IMPLEMENTED) == 0);
      
      /* summarize discard and modify based on expectation of discarded card */
      summarizeCards(preCards,  preState, PLAYER[i], DISCARD);
      summarizeCards(postCards, state,    PLAYER[i], DISCARD);

      postCards[discardedDeckCard]++;
      
      expect("Top deck card discarded... ", results,
        cmpArrays(preCards, N_CARDS_IMPLEMENTED, postCards, N_CARDS_IMPLEMENTED) == 0);
    }
  }
  
  testGameStateEquality(state, preState, equalitySet, results);
}


/*
 * establish the game state and ensure the player has a sea hag card
 */
void setupGameState (struct gameState * state, struct gameState * preState, int * pos)
{
  /* generate a random game state */
  randomGameState(state);
  
  /* give the player a sea hag */
  if (state->handCount[state->whoseTurn] > 0) {
    *pos = rand() % state->handCount[state->whoseTurn];
  } else {
    *pos = 0;
    state->handCount[state->whoseTurn] = 1;
  }
  state->hand[state->whoseTurn][*pos] = sea_hag;

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

  int i, pos, returnValue;
  struct gameState state;
  struct gameState preState;
  testSummary results;

  for (i = 0; i < N_TESTS; i++) {
    /* get a random game state and run the card */
    setupGameState(&state, &preState, &pos);
    returnValue = playCard(pos, 0, 0, 0, &state);
    
    printf("==== Test %6d ====\n", i + 1);
    printf(" == Pre-State == \n"); 
    printGameState(&preState);
    printf(" == Post-State ==\n");
    printGameState(&state);
    
    /* ensure the card should have run, then check post conditions */
    if (preState.numActions <= 0) {
      expect("No actions: expected failure... ", &results,
        returnValue == -1);
    } else if (preState.phase != 0) {
      expect("Wrong state: expected failure... ", &results,
        returnValue == -1);
    } else {
      expect("Expected success... ", &results,
        returnValue == 0);
      checkPostConditions(&state, &preState, &results);
    }
  }
  
  /* summarize results */
  printTestSummary(&results);
  return 0;
}
