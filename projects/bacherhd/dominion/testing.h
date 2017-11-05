#ifndef _TESTING_H_
#define _TESTING_H_

#include "dominion.h"

struct gameState;
typedef struct testSummary {
  int tests;
  int pass;
  int fail;
} testSummary;

enum {
  DECK    = 0x1, 
  HAND    = 0x2, 
  DISCARD = 0x4
};

enum { TEST_COST = 3 };

const int PLAYER[MAX_PLAYERS];
const int N_CARDS_IMPLEMENTED; 
const int SEED;
const int N_PLAYERS;
const int K_CARDS[10];
const int TEST_K_CARD;

/*
 *  returns the cards in a location, hand, deck or discards
 */
int * getCards (struct gameState * state, int player, int location);


/*
 *  returns the card count for a location: hand, deck or discards
 */
int getCardCount (struct gameState * state, int player, int location);


/*
 *  counts the treasures in a single array of cards
 *  Presumes treasures exist as enumerated values between copper and gold, inclusive.
 */
int countTreasures (int * array, int size);


/*
 *  counts the treasures for a given player in a given location
 *  location flags are stored in bits 1, 2 and 3 of location.
 */
int totalTreasures (struct gameState * state, int player, int location);


/* 
 * create a comparison array of two card summaries
 */
void compareCards (int * comparison, int * summaryA, int * summaryB);

/*
 *  create a card summary as an array of card counts, indexed by card type
 */
void summarizeCards (int * summary, struct gameState * state, int who, int where);


void printSummary (int * summary);

int sumTreasure (int * summary);

void compareStates (int * comparison, struct gameState * stateA, struct gameState * stateB, int who, int where);

void cpDeck (struct gameState * state, int player, int * srcDeck, int srcSize);

void expect (char * msg, testSummary * summary, int expectation);

void printTestSummary(testSummary * summary);

void cpState(struct gameState *dst, struct gameState * src);

int cardsUnchanged (struct gameState * stateA, struct gameState * stateB, int who, int where);


int randomCard(int * kCards);

void printSupplyCounts (struct gameState * state);

void printGameState (struct gameState * state);

void randomGameState (struct gameState * state);

#endif
