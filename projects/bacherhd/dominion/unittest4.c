/*******************************************************************************
* name: David Bacher-Hicks
* date: 22 October 2017
* description: unit tests for the isGameOver function
*******************************************************************************/

#include <stdio.h>

#include "dominion_helpers.h"
#include "cmpGameState.h"
#include "dominion.h"
#include "testing.h"

const int COST_IDX = 1; /* index of cost value */

/* although this array is parallel with the enum, cards repeated for clarity */
const int CARD_COST[treasure_map + 3][2] = {
  { curse,        0 },  
  { estate,       2 },
  { duchy,        5 },
  { province,     8 },
  { copper,       0 },
  { silver,       3 },
  { gold,         6 },
  { adventurer,   6 },
  { council_room, 5 },
  { feast,        4 },
  { gardens,      4 },
  { mine,         5 },
  { remodel,      4 }, 
  { smithy,       4 },
  { village,      3 },
  { baron,        4 },
  { great_hall,   3 },
  { minion,       5 },
  { steward,      3 },
  { tribute,      5 },
  { ambassador,   3 },
  { cutpurse,     4 },
  { embargo,      2 },
  { outpost,      5 },
  { salvager,     4 },
  { sea_hag,      4 },
  { treasure_map, 4 },     /* ^  valid cards  ^ */
  { -1,          -1 },     /* v invalid cards v */
  { treasure_map + 1, -1}
};

int main ()
{
  int i;

  /* initialize test results */
  testSummary results;
  results.tests = 0;
  results.pass = 0;
  results.fail = 0;

  printf("###########################\n");
  printf("#### getCost unit test ####\n");
  printf("###########################\n");

  /* test each card value and expected result */
  for(i = curse; i < treasure_map + 2; i++) {
    printf("Testing card %d\n", i);
    expect("card value: ", &results,
      getCost(i) == CARD_COST[i][COST_IDX]);
    printf("\n");
  }
  
  /* print results */
  printTestSummary(&results);
  return 0;
}
