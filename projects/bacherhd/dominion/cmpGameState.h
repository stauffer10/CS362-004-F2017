#ifndef _CMP_GAME_STATE_H_
#define _CMP_GAME_STATE_H_

#include "testing.h"
#include "dominion.h"

#include <assert.h>
#include <string.h>

const unsigned int GS_NUM_PLAYER_MASK;
const unsigned int GS_SUPPLY_COUNT_MASK; 
const unsigned int GS_EMBARGO_TOKENS_MASK;
const unsigned int GS_OUTPOST_PLAYED_MASK;
const unsigned int GS_OUTPOST_TURN_MASK;
const unsigned int GS_WHOSE_TURN_MASK;
const unsigned int GS_PHASE_MASK;      
const unsigned int GS_NUM_ACTIONS_MASK;
const unsigned int GS_COINS_MASK; 
const unsigned int GS_NUM_BUYS_MASK;
const unsigned int GS_HAND_MASK;
const unsigned int GS_DECK_MASK;
const unsigned int GS_DISCARD_MASK;
const unsigned int GS_PLAYED_CARDS_MASK;

const unsigned int GS_ALL;
const unsigned int GS_HAND_DECK_DISC;
const unsigned int GS_NOT_HAND_DECK_DISC;

int cmpArrays (int * A, int sizeA, int * B, int sizeB);
int cmpGameStateNumPlayers (struct gameState * A, struct gameState * B);
int cmpGameStateSupplyCount (struct gameState * A, struct gameState * B);
int cmpGameStateEmbargoTokens (struct gameState * A, struct gameState * B);
int cmpGameStateOutpostPlayed (struct gameState * A, struct gameState * B);
int cmpGameStateOutpostTurn (struct gameState * A, struct gameState * B);
int cmpGameStateWhoseTurn (struct gameState * A, struct gameState * B);
int cmpGameStatePhase(struct gameState * A, struct gameState * B);
int cmpGameStateNumActions(struct gameState * A, struct gameState * B);
int cmpGameStateCoins(struct gameState * A, struct gameState * B);
int cmpGameStateNumBuys(struct gameState * A, struct gameState * B);
int cmpGameStateHand(struct gameState * A, struct gameState * B);
int cmpGameStateDeck(struct gameState * A, struct gameState * B);
int cmpGameStateDiscard(struct gameState * A, struct gameState * B);
int cmpGameStatePlayedCards(struct gameState * A, struct gameState * B);
unsigned int cmpGameState (struct gameState * stateA, struct gameState * stateB);

void testGameStateEquality (struct gameState * A, struct gameState * B, 
  unsigned int equalSet, testSummary * results);

#endif
