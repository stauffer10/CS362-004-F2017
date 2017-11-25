/*******************************************************************************
* name: David Bacher-Hicks
* date: 22 October 2017
* description: unit tests for the cutpurse card
*******************************************************************************/

#include "testing.h"
#include "dominion.h"
#include "cmpGameState.h"
#include "cardEffects.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* player 0 starting hand */
const int P0_HAND_1[] = { cutpurse };
const int P0_HAND_2[] = { cutpurse, adventurer };
const int P0_HAND_3[] = { copper, cutpurse };
const int P0_HAND_SIZE[] = { 1, 2, 2 };
const int P0_HAND_POS[]  = { 0, 0, 1 };

/* player 1 starting hand */
const int P1_HAND[4][5] = {
  { adventurer, adventurer, adventurer, adventurer, adventurer },
  { adventurer, adventurer, adventurer, adventurer, copper },
  { copper, adventurer, adventurer, adventurer, adventurer },
  { copper, adventurer, adventurer, adventurer, copper }
};

/* expected hands */
const int P0_EXP_HAND_1[] = {};
const int P0_EXP_HAND_2[] = { adventurer };
const int P0_EXP_HAND_3[] = { copper };
const int P0_EXP_HAND_SIZE[] = { 0, 1, 1 };

const int P1_EXP_HAND_1[] = { adventurer, adventurer, adventurer, adventurer, adventurer };
const int P1_EXP_HAND_2[] = { adventurer, adventurer, adventurer, adventurer };
const int P1_EXP_HAND_3[] = { adventurer, adventurer, adventurer, adventurer };
const int P1_EXP_HAND_4[] = { copper, adventurer, adventurer, adventurer };
const int P1_EXP_HAND_SIZE[] = {5, 4, 4, 4};

/* possible discards */
const int EMPTY_DISCARD[] = { };
const int COPPER_DISCARD[] = { copper };

int main ()
{
  struct gameState initialState;
  struct gameState testState;
  struct gameState preState;
  int kCards[10] = { adventurer, great_hall, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room };

  if (initializeGame(N_PLAYERS, kCards, SEED, &initialState) == -1) {
    fprintf(stderr, "Couldn't init game state\n");
    exit(1);
  }

  printf("#################################\n");
  printf("#### cutpurse card unit test ####\n");
  printf("#################################\n");

  /* jagged arrays of hands */
  const int * p0Hands[] = { P0_HAND_1, P0_HAND_2, P0_HAND_3 };
  const int * p0ExpHands[] = { P0_EXP_HAND_1, P0_EXP_HAND_2, P0_EXP_HAND_3 };
  const int * p1ExpHands[] = { P1_EXP_HAND_1, P1_EXP_HAND_2, P1_EXP_HAND_3, P1_EXP_HAND_4 };

  /* initialize test summary struct */
  testSummary results;
  results.tests = 0;
  results.pass = 0;
  results.fail = 0;

  /* loop through hand possibilities and check against expectations */
  int iP0, iP1;
  for (iP0 = 0; iP0 < 3; iP0++) {
    for (iP1 = 0; iP1 < 4; iP1++) {
      printf("=== player 0 hand (%d), player 1 hand (%d) ===\n", iP0, iP1);
      /* reset state and copy hands */
      cpState(&testState, &initialState);
      memcpy(testState.hand[0], p0Hands[iP0], sizeof(int) * P0_HAND_SIZE[iP0]);
      memcpy(testState.hand[1], P1_HAND[iP1], sizeof(int) * 5);
      testState.handCount[1] = 5;
      testState.handCount[0] = P0_HAND_SIZE[iP0];

      /* update coins based on hand */
      updateCoins(0, &testState, 0);
      
      /* backup pre state */
      cpState(&preState, &testState);
      
      /* play cutpurse */
      int bonus = 0;
      cardEffect(cutpurse, 0, 0, 0, &testState, P0_HAND_POS[iP0], &bonus);
     
      /* check against expected changes */ 
      printf(" ===== Comparing Expected State Changes ===== \n");
      expect("coins increased by 2\t", &results, testState.coins == preState.coins + 2);
      
      /* hands and discards are as expected */
      expect("P0 Hand\t", &results,
        cmpArrays((int *) p0ExpHands[iP0], P0_EXP_HAND_SIZE[iP0],
          testState.hand[0], testState.handCount[0]) == 0);

      expect("P0 Discard\t", &results,
        cmpArrays((int *) EMPTY_DISCARD, 0, testState.discard[0], testState.discardCount[0]) == 0);
     
      expect("P1 Hand\t", &results,
        cmpArrays((int *) p1ExpHands[iP1], P1_EXP_HAND_SIZE[iP1], 
          testState.hand[1], testState.handCount[1]) == 0);
      
      /* expected discards for P1 depend on the iP1 value */
      if (iP1 == 0) {
        /* no discards */
        expect("P1 Discard\t", &results,
          cmpArrays((int *) EMPTY_DISCARD, 0, testState.discard[1], testState.discardCount[1]) == 0);
      } else {
        /* one copper in discards */
        expect("P1 Discard\t", &results,
          cmpArrays((int *) COPPER_DISCARD, 0, testState.discard[1], testState.discardCount[1]) == 0);
      }
      
      /* check all expected constant gamestate elements */
      printf(" ===== Comparing Expected Constants ===== \n");
      testGameStateEquality(&testState, &preState,
        (GS_NOT_HAND_DECK_DISC & (~GS_COINS_MASK) & (~GS_PLAYED_CARDS_MASK)) | GS_DECK_MASK, &results);
      printf("\n");
    }
  }
  
  /* print the test results */
  printTestSummary(&results);
  return 0;
}
