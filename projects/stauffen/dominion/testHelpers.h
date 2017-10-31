//testHelpers.h

#include "dominion.h"

#ifndef TESTHELPERS_H
#define TESTHELPERS_H

int intAssert(int received, int expected);
void compareKC(struct gameState *G1, struct gameState *G2);
void compareVC(struct gameState *G1, struct gameState *G2);
void comparePlayerDeckStates(int player, struct gameState *G1, struct gameState *G2);
void randomizeGameState(int numberOfPlayers, int kCards[10], struct gameState *G1);
void pushString(char *arr[], int length, char *string);

#endif
