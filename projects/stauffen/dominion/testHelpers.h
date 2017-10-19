//testHelpers.h

#include "dominion.h"

#ifndef TESTHELPERS.H
#define TESTHELPERS.H

void intAssert(int received, int expected);
void compareKC(struct gameState *G1, struct gameState *G2);
void compareVC(struct gameState *G1, struct gameState *G2);
void comparePlayerDeckStates(int player, struct gameState *G1, struct gameState *G2);

#endif
