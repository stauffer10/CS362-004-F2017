/*******************************************************************************
* name: David Bacher-Hicks
* date: 22 October 2017
* description: unit tests for the isGameOver function
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "dominion_helpers.h"
#include "cmpGameState.h"
#include "dominion.h"
#include "testing.h"

enum { N_EMPTY_SETS = 6 };

const int TEST_CARDS[] = { curse, copper, adventurer, treasure_map };
const int THREE_EMPTY[N_EMPTY_SETS] = {0, 0, 0, 1, 1, 1};
const int IS_EMPTY[N_EMPTY_SETS][4] = {
  {0, 0, 0, 0}, /* none empty */
  {0, 0, 1, 1}, /* two empty */
  {1, 1, 0, 0},
  {0, 1, 1, 1}, /* three empty */
  {1, 1, 1, 0},
  {1, 1, 1, 1} /* all empty */
};


/*
 *  for every bit in the empty set map, 
 *    if 0: set corresponding supply count to 20, 
 *    if 1: set corresponding supply count to 0
 */
void setEmptyPiles (struct gameState * state, unsigned int emptySet)
{
  int i;
  unsigned int cardMask = 0x1;
  for (i = 0; i < N_CARDS_IMPLEMENTED; i++) {
    if (emptySet & cardMask) {
      state->supplyCount[i] = 0;  
    } else {
      state->supplyCount[i] = 20;
    }
    cardMask <<= 1; 
  }
}


/*
 *  set the bit associated with the card in the empty set
 */
void addToEmptySet (unsigned int * emptySet, int card)
{
  if (emptySet) *emptySet |= (0x1 << card);
}


/*
 *  set the empty set based on an array defining which of the
 *  test cards should be empty. Province is a special case, 
 *  its empty status is passed in as a bool
 */
unsigned int defineEmptySet (int * emptyArray, int provinceIsEmpty)
{
  int i;
  unsigned int emptySet = 0x0;

  for (i = 0; i < 4; i++) {
    if (emptyArray[i]) addToEmptySet(&emptySet, TEST_CARDS[i]);
  }

  if (provinceIsEmpty) addToEmptySet(&emptySet, province);

  return emptySet;
}


int main ()
{
  struct gameState initialState;
  struct gameState testState;
  struct gameState preState;
  
  if (initializeGame(N_PLAYERS, (int *) K_CARDS, SEED, &initialState) == -1) {
    fprintf(stderr, "Couldn't initialize game state\n");
    exit(1);
  }

  printf("##############################\n");
  printf("#### isGameOver unit test ####\n");
  printf("##############################\n");

  int provinceIsEmpty, i, returnValue;

  /* initialize test summary */
  testSummary results;
  results.tests = 0;
  results.pass = 0;
  results.fail = 0;

  /* loop through empty sets and province being empty or not */
  for (provinceIsEmpty = 0; provinceIsEmpty < 2; provinceIsEmpty++) {
    for (i = 0; i < N_EMPTY_SETS; i++) {
      printf("Testing provinceEmpty=%d, three empty=%d\n", provinceIsEmpty, THREE_EMPTY[i]);
      
      /* restore from initial state, set the empty piles, and backup the prestate  */
      cpState(&testState, &initialState);
      setEmptyPiles(&testState, defineEmptySet((int *) IS_EMPTY[i], provinceIsEmpty));
      cpState(&preState, &testState);
     
      /* run the function and check the return value */
      returnValue = isGameOver(&testState);
      expect("isGameOver() return value ", &results,
        returnValue == (THREE_EMPTY[i] || provinceIsEmpty));
      
      /* confirm that the gamestate has not been changed */
      printf("Confirming gamestate unchanged\n"); 
      testGameStateEquality(&testState, &preState, GS_ALL, &results); 
    } 
  }
  
  /* print test results */
  printTestSummary(&results);
  return 0; 
}
