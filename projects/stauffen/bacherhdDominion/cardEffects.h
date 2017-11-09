#ifndef _CARD_EFFECTS_H_
#define _CARD_EFFECTS_H_

#include <stdio.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"

int caAdventurer(struct gameState * state, int currentPlayer);
int caCutpurse(struct gameState * state, int currentPlayer, int handPos);
int caGreatHall(struct gameState * state, int currentPlayer, int handPos);
int caSeaHag(struct gameState * state, int currentPlayer);
int caSmithy(struct gameState * state, int currentPlayer, int handPos);

#endif
