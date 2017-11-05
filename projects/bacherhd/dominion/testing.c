/*******************************************************************************
* name: David Bacher-Hicks
* date: 22 October 2017
* description: various functions to assist in performing unit tests on the dominion
* implementation.
*******************************************************************************/

#include "dominion.h"
#include "testing.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int SEED = 42;
const int N_PLAYERS = 2;
const int K_CARDS[10] = { adventurer, great_hall, village, minion, mine, cutpurse,
                          sea_hag, tribute, smithy, council_room };

const int TEST_K_CARD = great_hall;

const int PLAYER[] = {0x1, 0x2, 0x4, 0x8};
const int N_CARDS_IMPLEMENTED = 27;
const char * C_ABV[] = {
  "CRS", "EST", "DCH", "PRV", "CPR", "SLV", "GLD", "ADV", "CRM", "FST", 
  "GDN", "MNE", "RMD", "SMT", "VIL", "BAR", "GRT", "MIN", "STW", "TRB",
  "AMB", "CTP", "BGO", "OTP", "SAL", "HAG", "MAP"
};


/*
 *  initialize a standard gamestate
 */
int genGameState (struct gameState * state)
{
  return initializeGame(N_PLAYERS, (int *) K_CARDS, SEED, state);
}


int randomCard(int * kCards)
{
  int i = rand() % (adventurer + 1);
  if (i == adventurer) 
    i = kCards[rand() % 10];
  return i;
}

void printSupplyCounts (struct gameState * state)
{
  int i, j;
  for (j = 0; j < 2; j++) {
    for (i = 0; i < N_CARDS_IMPLEMENTED; i++) {
      if (j == 0) {
        printf("%4s", C_ABV[i]);
      } else if (j == 1) {
        printf("%4d", state->supplyCount[i]);
      }
    }
    printf("\n");
  }
}

void printGameState (struct gameState * state)
{
  int summary[N_CARDS_IMPLEMENTED];

  printf("Player %d's turn\n", state->whoseTurn);

  printf("nPlayers: %d, numActions: %d, coins: %d\n", state->numPlayers, state->numActions, state->coins);
  printf("hand count: %d, deck count: %d, discard count: %d\n", 
    state->handCount[state->whoseTurn], state->deckCount[state->whoseTurn], state->discardCount[state->whoseTurn]);

  printf("Supply Counts...\n");
  printSupplyCounts(state);
  
  printf("Hand...\n");
  summarizeCards(summary, state, PLAYER[state->whoseTurn], HAND);
  printSummary(summary);

  printf("Deck...\n");
  summarizeCards(summary, state, PLAYER[state->whoseTurn], DECK);
  printSummary(summary);
}

void randomGameState (struct gameState * state)
{
  state->numPlayers = rand() % MAX_PLAYERS + 1;

  int i, j, nChoices;
  int kCards[10];
  nChoices = treasure_map - adventurer + 1;
  int kCardChoices[nChoices];
  
  /* set the possible values */
  j = 0;
  for (i = adventurer; i <= treasure_map; i++) {
    kCardChoices[j++] = i; 
  }

  /* init curse, estate, duchy, province, copper, silver and gold to [0, 100] */
  for (i = 0; i <= gold; i++) state->supplyCount[i] = rand() % 20;
  
  /* init kingdom cards to -1 */
  for (i = adventurer; i <= treasure_map; i++) {
    state->supplyCount[i] = -1;
  } 

  for (i = 0; i <= treasure_map; i++) {
    state->embargoTokens[i] = rand() % 5;
  }

  int choice;

  /* choose kingdom cards, set supplies */
  for (i = 0; i < 10; i++) {
    choice = rand() % nChoices;
    kCards[i] = kCardChoices[choice];
    kCardChoices[choice] = kCardChoices[nChoices - 1];
    nChoices--;
    state->supplyCount[kCards[i]] = rand() % 20;
  }
  
  state->outpostPlayed = 0;
  state->outpostTurn   = 0;
  state->whoseTurn     = rand() % state->numPlayers;
  state->phase         = 0;
  state->numActions    = rand() % 100;
  state->coins         = rand() % 100;
  state->numBuys       = rand() % 100;
  
  for (i = 0; i < state->numPlayers; i++) {

    state->deckCount[i]    = rand() %  MAX_DECK;
    state->handCount[i]    = rand() % (MAX_DECK - state->deckCount[i]);
    state->discardCount[i] = rand() % (MAX_DECK - state->deckCount[i] - state->handCount[i]);
    state->playedCardCount = rand() % (MAX_DECK - 
      state->deckCount[i] - state->handCount[i] - state->discardCount[i]);

    for (j = 0; j < state->handCount[i]; j++) {
      state->hand[i][j] = randomCard(kCards);  
    }

    for (j = 0; j < state->deckCount[i]; j++) {
      state->deck[i][j] = randomCard(kCards);
    }

    for (j = 0; j < state->discardCount[i]; j++) {
      state->discard[i][j] = randomCard(kCards);
    }

    for (j = 0; j < state->playedCardCount; j++) {
      state->playedCards[j] = randomCard(kCards);
    }

  }
}


/*
 *  an assert like statement that prints a message and adds the result
 *  to the passed in summary structure
 */
void expect (char * msg, testSummary * summary, int expectation)
{
  printf("%s", msg);
  if (expectation) {
    printf("PASS\n");
    summary->pass++;
  } else {
    printf("FAIL\n");
    summary->fail++;
  }
  summary->tests++;
}


/*
 *  print the summary results of the test
 */
void printTestSummary (testSummary * summary) 
{
  printf("Completed %d tests", summary->tests);
  if (summary->pass > 0 && summary->fail == 0) {
    printf(" with no failures\n");
  } else {
    printf(" with %d passes and %d failures.\n", summary->pass, summary->fail);
  }
}


/*
 *  returns the cards in a location, hand, deck or discards
 */
int * getCards (struct gameState * state, int player, int location)
{
  assert(state);
  assert(player < state->numPlayers);

  switch (location) {
    case DECK:    return state->deck[player];
    case HAND:    return state->hand[player];
    case DISCARD: return state->discard[player];
    default:
      fprintf(stderr, "Unhandled location, %d\n", location);
      break;
  }

  return NULL;
}


/*
 *  returns the card count for a location: hand, deck or discards
 */
int getCardCount (struct gameState * state, int player, int location)
{
  assert(state);
  assert(player < state->numPlayers);

  switch (location) {
    case DECK:    return state->deckCount[player];
    case HAND:    return state->handCount[player];
    case DISCARD: return state->discardCount[player];
    default:
      fprintf(stderr, "Unhandled location, %d\n", location);
  }

  return -1;
}


/*
 *  counts the treasures in a single array of cards
 *  Presumes treasures exist as enumerated values between copper and gold, inclusive.
 */
int countTreasures (int * array, int size)
{
  int i;
  int c = 0;
  for (i = 0; i < size; i++) {
    if (array[i] >= copper && array[i] <= gold) c++;
  }
  return c;
}


/*
 *  counts the treasures for a given player in a given location
 *  location flags are stored in bits 1, 2 and 3 of location.
 */
int totalTreasures (struct gameState * state, int player, int location)
{
  int treasureCount = 0;

  if (location & DECK) {
    treasureCount += countTreasures(state->deck[player],
      state->deckCount[player]);
  }

  if (location & HAND) {
    treasureCount += countTreasures(state->hand[player],
      state->handCount[player]);
  }

  if (location & DISCARD) {
    treasureCount += countTreasures(state->discard[player],
      state->discardCount[player]);
  }
  
  return treasureCount;
}


/*
 * compares the card summaries between two states for a given player(s) in a given location(s)
 */
void compareStates (int * comparison, struct gameState * stateA, struct gameState * stateB, int who, int where)
{
  int summaryA[N_CARDS_IMPLEMENTED];
  int summaryB[N_CARDS_IMPLEMENTED];

  summarizeCards(summaryA, stateA, who, where);
  summarizeCards(summaryB, stateB, who, where);

  compareCards(comparison, summaryA, summaryB);
}


/*
 *  returns whether or not the cards are identical between two states for a given player or
 *  players in a given location or locations.
 */
int cardsUnchanged (struct gameState * stateA, struct gameState * stateB, int who, int where)
{
  int summaryA[N_CARDS_IMPLEMENTED];
  int summaryB[N_CARDS_IMPLEMENTED];

  summarizeCards(summaryA, stateA, who, where);
  summarizeCards(summaryB, stateB, who, where);

  return memcmp(summaryA, summaryB, N_CARDS_IMPLEMENTED);
}


/* 
 * create a comparison array of two card summaries as a difference in the values
 */
void compareCards (int * comparison, int * summaryA, int * summaryB)
{
  int i;
  for (i = 0; i < N_CARDS_IMPLEMENTED; i++) {
    comparison[i] = summaryA[i] - summaryB[i];
  }
}


/*
 * print a card summary with card abbreviations
 */
void printSummary (int * summary)
{
  int i = 0;
  for (i = 0; i < N_CARDS_IMPLEMENTED; i++) {
    printf("%4s", C_ABV[i]);
  }
  printf("\n");
  for (i = 0; i < N_CARDS_IMPLEMENTED; i++) {
    printf("%4d", summary[i]);
  }
  printf("\n");
}


/*
 * creates a summary of cards for a game state, given a combination of player or players
 * and location or locations. All cards in those locations for those players will be 
 * counted and placed into an array, parallel with the card enum
 *
 * Useful when comparing card collections when order doesn't matter 
 */
void summarizeCards (int * summary, struct gameState * state, int who, int where)
{
  int player   = 1;
  int location = DECK;
  int * cards  = NULL;
  int nCards   = 0;
  int i;
  
  /* clear summary */
  memset(summary, 0, N_CARDS_IMPLEMENTED * sizeof(*summary));
  
  /* 
   * for every player and every location indicated by who and where,
   *  increment the summary at the appropriate index 
   */
  for (player = 0; player < MAX_PLAYERS; player++) {
    for (location = DECK; location <= DISCARD; location <<= 1) {
      if ( (who & PLAYER[player]) && (where & location) ) {
        cards  = getCards(state, player, location);
        nCards = getCardCount(state, player, location);

        if ((cards != NULL) && (nCards > 0)) {
          for (i = 0; i < nCards; i++) {
            summary[cards[i]]++;
          }
        }
      }
    }
  }
}


/*
 * sum and return the treasure count in a card summary
 */
int sumTreasure (int * summary)
{
  return summary[gold] + summary[silver] + summary[copper]; 
}


/*
 * copy a deck from a source deck array to a player in the gamestate
 */
void cpDeck (struct gameState * state, int player, int * srcDeck, int srcSize) {
  int i = 0;
  for (i = 0; i < srcSize; i++) {
    state->deck[player][i] = srcDeck[i];
  }
  state->deckCount[player] = srcSize;
}


/*
 * copy one gamestate to another
 */
void cpState(struct gameState * dst, struct gameState * src) {
  memcpy(dst, src, sizeof(*src));
}
