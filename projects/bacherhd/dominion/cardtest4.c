/*******************************************************************************
* name: David Bacher-Hicks
* date: 22 October 2017
* description: unit tests for the smithy card
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "dominion.h"
#include "testing.h"
#include "cardEffects.h"
#include "cmpGameState.h"

/* deck cards to use */
const int DECKS[8] = { copper, silver, gold, adventurer, village, 
                     mine, cutpurse, sea_hag };

/* deck sizes ot use */
const int DECK_SIZES[3]= { 0, 2, 8 };

/* hands to use */
const int HANDS[2][5] = {
  { smithy, copper, copper, copper, copper },
  { copper, copper, copper, copper, smithy }};

/* smithy position in HANDS[i] */
const int SMITHY_POS[2] = { 0, 4 };

int main ()
{
  struct gameState initialState;
  struct gameState testState;
  struct gameState preState;
  
  /* define elements of gamestate expected to remain constant */
  const unsigned int EXPECTED_SET = GS_NOT_HAND_DECK_DISC & ~GS_PLAYED_CARDS_MASK;
  
  int kCards[] = { adventurer, great_hall, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room };

  if (initializeGame(N_PLAYERS, kCards, SEED, &initialState) == -1) {
    fprintf(stderr, "Couldn't init game state\n");
  }

  printf("###############################\n");
  printf("#### smithy card unit test ####\n");
  printf("###############################\n");

  /* initialize test summary */
  testSummary results;
  results.tests = 0;
  results.pass = 0;
  results.fail = 0;
  
  /* loop through hands and decks */
  int i, j;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {

      printf("\nTesting hand config: ");
      printf("smithy at pos %d, deck size %d\n", SMITHY_POS[i], DECK_SIZES[j]);
      
      /* reset test state, copy in hand and deck, backup into preState */
      cpState(&testState, &initialState);
      memcpy(testState.hand[0], HANDS[i], sizeof(int) * 5);
      testState.handCount[0] = 5;
      memcpy(testState.deck[0], DECKS, sizeof(int) * DECK_SIZES[j]);
      testState.deckCount[0] = DECK_SIZES[j];
      cpState(&preState, &testState); 
      
      /* use smithy card */
      int bonus = 0;
      cardEffect(smithy, 0, 0, 0, &testState, SMITHY_POS[i], &bonus);
      
      /* expected changes */ 

      /* develop an expected cards summary array from the hand + top three deck cards */
      int expectedDrawnCards[N_CARDS_IMPLEMENTED];
      int resultingHand[N_CARDS_IMPLEMENTED];
      summarizeCards(expectedDrawnCards, &preState, PLAYER[0], HAND);
      summarizeCards(resultingHand, &testState, PLAYER[0], HAND);

      /* set number of expected drawn cards based on deck size, up to 3 cards */ 
      int toDraw = preState.deckCount[0] < 3 ? preState.deckCount[0] : 3;
      int toDiscard = 1;

      /* update the expected cards for draws and discards */
      int k;
      for (k = preState.deckCount[0] - toDraw; k < preState.deckCount[0]; k++) {
        expectedDrawnCards[preState.deck[0][k]]++; 
      }
      expectedDrawnCards[smithy]--;

      /* check hand count and change in cards */ 
      expect("Expected hand results ", &results,
        cmpArrays(expectedDrawnCards, N_CARDS_IMPLEMENTED, resultingHand, N_CARDS_IMPLEMENTED) == 0);

      expect("Player 0 hand count net change ", &results,
        testState.handCount[0] == preState.handCount[0] + toDraw - toDiscard);
        
      expect("Player 0 discard count change +1 ", &results,
        testState.discardCount[0] == preState.discardCount[0] + 1);
      
      /* check smithy is in discards */
      int expectedDiscards[N_CARDS_IMPLEMENTED];
      summarizeCards(expectedDiscards, &preState, PLAYER[0], DISCARD);
      expectedDiscards[smithy]++;
      expect("Player 0 discards contains one extra smithy\t", &results,
        cmpArrays(expectedDiscards, N_CARDS_IMPLEMENTED, testState.discard[0], N_CARDS_IMPLEMENTED) == 0);

      /* player 1 expected unchanged elements */
      expect("Player 1 hand count unchanged\t", &results,
        testState.discardCount[1] == preState.discardCount[1]);

      expect("Player 1 hand unchanged\t\t", &results,
        cmpArrays(preState.hand[1], preState.handCount[1], 
                  testState.hand[1], testState.handCount[1]) == 0);    
      
      expect("Player 1 deck unchanged\t\t", &results,
        cmpArrays(preState.deck[1], preState.deckCount[1], 
                  testState.deck[1], testState.deckCount[1]) == 0);

      expect("Player 1 discards unchanged\t", &results,
        cmpArrays(preState.discard[1], preState.discardCount[1], 
                  testState.discard[1], testState.discardCount[1]) == 0);

      /* test all other gamestate elements expected to remain unchanged */
      testGameStateEquality(&testState, &preState, EXPECTED_SET, &results);
    }
  }  

  /* print test results */
  printTestSummary(&results);
  return 0;
}
