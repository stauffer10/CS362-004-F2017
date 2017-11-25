/*******************************************************************************
* name: David Bacher-Hicks
* date: 22 October 2017
* description: unit tests for the great hall card
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "dominion.h"
#include "testing.h"
#include "cmpGameState.h"

int main ()
{
  struct gameState initialState;
  struct gameState testState;
  struct gameState preState;
  
  /* define expected constant gamestate elements */
  const unsigned int EXPECTED_SET = GS_ALL & ~GS_HAND_MASK & ~GS_DECK_MASK 
          & ~GS_DISCARD_MASK & ~GS_PLAYED_CARDS_MASK & ~GS_NUM_ACTIONS_MASK;
  
  int kCards[] = { adventurer, great_hall, village, minion, mine, cutpurse,
                   sea_hag, tribute, smithy, council_room }; 

  if (initializeGame(N_PLAYERS, kCards, SEED, &initialState) == -1) {
    fprintf(stderr, "Couldn't init game state\n");
    exit(1);
  }

  printf("###################################\n");
  printf("#### great hall card unit test ####\n");
  printf("###################################\n");

  /* initialize test summary */
  testSummary results;
  results.tests = 0;
  results.fail = 0;
  results.pass = 0;
  
  /* copy initial state */
  cpState(&testState, &initialState); 
  
  /* get top deck card and set great hall to hand card 0 */
  int oldDeckCount = testState.deckCount[0];
  int topCard = testState.deck[0][oldDeckCount - 1];
  testState.hand[0][0] = great_hall;
  
  /* backup test state in prestate and use great hall */
  cpState(&preState, &testState);
  int bonus = 0;
  cardEffect(great_hall, 0, 0, 0, &testState, 0, &bonus);

  printf("\n === Checking Player 0 Changed State ===\n");

  /* check expected changes */
  expect("Deck size decremented by 1 ", &results,
    testState.deckCount[0] == preState.deckCount[0] - 1);

  expect("Top card drawn into hand ", &results,
    testState.hand[0][testState.handCount[0] - 1] == topCard);
  
  expect("Actions incremented ", &results,
    testState.numActions = preState.numActions + 1);
    
  printf("\n === Checking Player 1 Cards Unchanged ===\n");
  
  /* check player 1 cards */
  expect("Player 1 hand unchanged\t\t", &results,
    cardsUnchanged(&preState, &testState, PLAYER[1], HAND) == 0);

  expect("Player 1 deck unchanged\t\t", &results,
    cardsUnchanged(&preState, &testState, PLAYER[1], DECK) == 0);

  expect("Player 1 discards unchanged\t", &results,
    cardsUnchanged(&preState, &testState, PLAYER[1], DISCARD) == 0);

  printf("\n === Checking Unchanged Elements in Game State ===\n");
  
  /* check static elements */
  testGameStateEquality(&testState, &preState, EXPECTED_SET, &results);

  /* develop card summaries, pre and post, of all cards and check that they're unchanged */
  int cardSummary[N_CARDS_IMPLEMENTED];
  int cardSummaryPost[N_CARDS_IMPLEMENTED];
  summarizeCards(cardSummary,     &preState,  PLAYER[0] | PLAYER[1], DECK | HAND | DISCARD);
  summarizeCards(cardSummaryPost, &testState, PLAYER[0] | PLAYER[1], DECK | HAND | DISCARD);
  
  expect("Cards in play (deck, hand, discard) unchanged ", &results,
    cmpArrays(cardSummary, N_CARDS_IMPLEMENTED, cardSummaryPost, N_CARDS_IMPLEMENTED) == 0);
  
  /* print results */
  printTestSummary(&results);

  return 0;
}
