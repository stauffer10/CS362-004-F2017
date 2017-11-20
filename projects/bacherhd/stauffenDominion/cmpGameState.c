/*******************************************************************************
* name: David Bacher-Hicks
* date: 22 October 2017
* description: functions to help automate comparing components of game state 
* that are expected to remain unchanged. Uses a bitmap for elements in game state
* expected to be equal, then runs tests on every presumed equal element, keeping
* track using a test summary struct, as defined in testing.c
*
* All comparison functions return 0 when elements are equal, or some non-zero
* value if not equal, normally -1
*******************************************************************************/

#include "testing.h"
#include "dominion.h"
#include "cmpGameState.h"
#include <assert.h>
#include <string.h>

/* gamestate element masks */
const unsigned int GS_NUM_PLAYER_MASK      = 0x0001;
const unsigned int GS_SUPPLY_COUNT_MASK    = 0x0002;
const unsigned int GS_EMBARGO_TOKENS_MASK  = 0x0004;
const unsigned int GS_OUTPOST_PLAYED_MASK  = 0x0008;
const unsigned int GS_OUTPOST_TURN_MASK    = 0x0010;
const unsigned int GS_WHOSE_TURN_MASK      = 0x0020;
const unsigned int GS_PHASE_MASK           = 0x0040;
const unsigned int GS_NUM_ACTIONS_MASK     = 0x0080;
const unsigned int GS_COINS_MASK           = 0x0100;
const unsigned int GS_NUM_BUYS_MASK        = 0x0200;
const unsigned int GS_HAND_MASK            = 0x0400;
const unsigned int GS_DECK_MASK            = 0x0800;
const unsigned int GS_DISCARD_MASK         = 0x1000;
const unsigned int GS_PLAYED_CARDS_MASK    = 0x2000;

const unsigned int GS_ALL                  = 0x3FFF; /* all elements */
const unsigned int GS_HAND_DECK_DISC       = 0x0C00; /* just hand, deck and discard */
const unsigned int GS_NOT_HAND_DECK_DISC   = 0x23FF; /* everything but hand, deck, and discard */

/*
 * Compare two arrays, return the memcmp value or -1 if the sizes do not match
 */
int cmpArrays (int * A, int sizeA, int * B, int sizeB)
{
  if (sizeA != sizeB) return -1;
  return memcmp(A, B, sizeof(int) * sizeA);
}

/*
 * Compare number of players
 */
int cmpGameStateNumPlayers (struct gameState * A, struct gameState * B)
{
  if (A->numPlayers == B->numPlayers) return 0;
  else return 1;
}

/*
 *  Compare supply count
 */
int cmpGameStateSupplyCount (struct gameState * A, struct gameState * B)
{
  int n = treasure_map + 1;
  return cmpArrays(A->supplyCount, n, B->supplyCount, n);
}

/*
 * Compare embargo tokens
 */
int cmpGameStateEmbargoTokens (struct gameState * A, struct gameState * B)
{
  int n = treasure_map + 1;
  return cmpArrays(A->embargoTokens, n, B->embargoTokens, n);
}

/*
 *  Compare outpost played
 */
int cmpGameStateOutpostPlayed (struct gameState * A, struct gameState * B)
{
  if (A->outpostPlayed == B->outpostPlayed) return 0;
  else return -1;
}

/*
 * Compare outpost turn
 */
int cmpGameStateOutpostTurn (struct gameState * A, struct gameState * B)
{
  if (A->outpostTurn == B->outpostTurn) return 0;
  else return -1;
}

/*
 * Compare whose turn
 */
int cmpGameStateWhoseTurn (struct gameState * A, struct gameState * B)
{
  if (A->whoseTurn == B->whoseTurn) return 0;
  else return -1;
}

/*
 * Compare phase
 */
int cmpGameStatePhase(struct gameState * A, struct gameState * B)
{
  if (A->phase == B->phase) return 0;
  else return -1;
}

/*
 * Compare number of actions
 */
int cmpGameStateNumActions(struct gameState * A, struct gameState * B)
{
  if (A->numActions == B->numActions) return 0;
  else return -1;
}

/*
 * Compare coins
 */
int cmpGameStateCoins(struct gameState * A, struct gameState * B)
{
  if (A->coins == B->coins) return 0;
  else return -1;
}

/*
 * Compare buys
 */
int cmpGameStateNumBuys(struct gameState * A, struct gameState * B)
{
  if (A->numBuys == B->numBuys) return 0;
  else return -1;
}

/*
 *  Compare hands
 */
int cmpGameStateHand(struct gameState * A, struct gameState * B)
{
  int i, n;
  n = A->numPlayers < B->numPlayers ? A->numPlayers : B->numPlayers; 
  int playerEquality = 0x0;

  for(i = 0; i < n; i++) {
    if (cmpArrays(A->hand[i], A->handCount[i], B->hand[i], B->handCount[i]) != 0)
      playerEquality |= PLAYER[i];    
  }

  return playerEquality;
}

/*
 *  Compare decks
 */
int cmpGameStateDeck(struct gameState * A, struct gameState * B)
{
  int i, n;
  n = A->numPlayers < B->numPlayers ? A->numPlayers : B->numPlayers; 
  int playerEquality = 0x0;

  for(i = 0; i < n; i++) {
    if (cmpArrays(A->deck[i], A->deckCount[i], B->deck[i], B->deckCount[i]) != 0)
      playerEquality |= PLAYER[i];    
  }

  return playerEquality;
}

/*
 * Compare discards
 */
int cmpGameStateDiscard(struct gameState * A, struct gameState * B)
{
  int i, n;
  n = A->numPlayers < B->numPlayers ? A->numPlayers : B->numPlayers; 
  int playerEquality = 0x0;

  for(i = 0; i < n; i++) {
    if (cmpArrays(A->discard[i], A->discardCount[i], B->discard[i], B->discardCount[i]) != 0)
      playerEquality |= PLAYER[i];    
  }

  return playerEquality;
}

/*
 * Compare played cards
 */
int cmpGameStatePlayedCards(struct gameState * A, struct gameState * B)
{
  return cmpArrays(A->playedCards, A->playedCardCount, B->playedCards, B->playedCardCount);
}

/*
 *  Compares two gamestates and returns a bit map with bits set for every non-equal element 
 */
unsigned int cmpGameState (struct gameState * stateA, struct gameState * stateB) 
{
  assert((stateA != NULL) && (stateB != NULL));
  unsigned int gameStateEquality = 0x0;

  if (cmpGameStateNumPlayers(stateA, stateB)    != 0) gameStateEquality |= GS_NUM_PLAYER_MASK;
  if (cmpGameStateSupplyCount(stateA, stateB)   != 0) gameStateEquality |= GS_SUPPLY_COUNT_MASK;
  if (cmpGameStateEmbargoTokens(stateA, stateB) != 0) gameStateEquality |= GS_EMBARGO_TOKENS_MASK;
  if (cmpGameStateOutpostPlayed(stateA, stateB) != 0) gameStateEquality |= GS_OUTPOST_PLAYED_MASK;
  if (cmpGameStateOutpostTurn(stateA, stateB)   != 0) gameStateEquality |= GS_OUTPOST_TURN_MASK;
  if (cmpGameStateWhoseTurn(stateA, stateB)     != 0) gameStateEquality |= GS_WHOSE_TURN_MASK;
  if (cmpGameStatePhase(stateA, stateB)         != 0) gameStateEquality |= GS_PHASE_MASK;         
  if (cmpGameStateNumActions(stateA, stateB)    != 0) gameStateEquality |= GS_NUM_ACTIONS_MASK;
  if (cmpGameStateCoins(stateA, stateB)         != 0) gameStateEquality |= GS_COINS_MASK;         
  if (cmpGameStateNumBuys(stateA, stateB)       != 0) gameStateEquality |= GS_NUM_BUYS_MASK;
  if (cmpGameStateHand(stateA, stateB)          != 0) gameStateEquality |= GS_HAND_MASK;          
  if (cmpGameStateDeck(stateA, stateB)          != 0) gameStateEquality |= GS_DECK_MASK;          
  if (cmpGameStateDiscard(stateA, stateB)       != 0) gameStateEquality |= GS_DISCARD_MASK;
  if (cmpGameStatePlayedCards(stateA, stateB)   != 0) gameStateEquality |= GS_PLAYED_CARDS_MASK;

  return gameStateEquality;
}

/*
 * compares two gamestates and expects every element specified in the equalSet bit map 
 * to be equal. Results are recorded in the results testSummary 
 */
void testGameStateEquality (struct gameState * A, struct gameState * B, 
  unsigned int equalSet, testSummary * results) 
{
  unsigned int equalityResults = cmpGameState(A, B);

  if (equalSet & GS_NUM_PLAYER_MASK) 
    expect("num player\t", results, !(GS_NUM_PLAYER_MASK & equalityResults));

  if (equalSet & GS_SUPPLY_COUNT_MASK) 
    expect("supply count\t", results, !(GS_SUPPLY_COUNT_MASK & equalityResults));

  if (equalSet & GS_EMBARGO_TOKENS_MASK)
    expect("embargo tokens\t", results, !(GS_EMBARGO_TOKENS_MASK & equalityResults));

  if (equalSet & GS_OUTPOST_PLAYED_MASK)
    expect("outpost played\t", results, !(GS_OUTPOST_PLAYED_MASK & equalityResults));

  if (equalSet & GS_OUTPOST_TURN_MASK)
    expect("outpost turn\t", results, !(GS_OUTPOST_TURN_MASK & equalityResults));

  if (equalSet & GS_WHOSE_TURN_MASK)
    expect("whose turn\t", results, !(GS_WHOSE_TURN_MASK & equalityResults));

  if (equalSet & GS_PHASE_MASK)
    expect("phase\t\t", results, !(GS_PHASE_MASK & equalityResults));

  if (equalSet & GS_NUM_ACTIONS_MASK)
    expect("num actions\t", results, !(GS_NUM_ACTIONS_MASK & equalityResults));

  if (equalSet & GS_COINS_MASK)
    expect("coins\t\t", results, !(GS_COINS_MASK & equalityResults));

  if (equalSet & GS_NUM_BUYS_MASK)
    expect("num buys\t", results, !(GS_NUM_BUYS_MASK & equalityResults));

  if (equalSet & GS_HAND_MASK)
    expect("hand\t\t", results, !(GS_HAND_MASK & equalityResults));

  if (equalSet & GS_DECK_MASK)
    expect("deck\t\t", results, !(GS_DECK_MASK & equalityResults));

  if (equalSet & GS_DISCARD_MASK)
    expect("discard\t\t", results, !(GS_DISCARD_MASK & equalityResults));

  if (equalSet & GS_PLAYED_CARDS_MASK)
    expect("played cards\t", results, !(GS_PLAYED_CARDS_MASK & equalityResults));
} 
