#include "cardEffects.h"

int caAdventurer(struct gameState * state, int currentPlayer)
{
  int drawnTreasure = 0;
  int temphand[MAX_HAND];
  int tempHandCounter = 0;
  int cardDrawn;

  while (drawnTreasure <= 2) {
    //if the deck is empty we need to shuffle discard and add to deck
    if (state->deckCount[currentPlayer] < 1) {
      shuffle(currentPlayer, state);
    }
    drawCard(currentPlayer, state);

    //top card of hand is most recently drawn card.
    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      drawnTreasure++;
    else {
      temphand[tempHandCounter]=cardDrawn;
      state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
      tempHandCounter++;
    }
  }

  while( tempHandCounter - 1 >= 0) {
    // discard all cards in play that have been drawn
    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[tempHandCounter-1]; 
    tempHandCounter = tempHandCounter - 1;
  }

  return 0;
}


int caCutpurse(struct gameState * state, int currentPlayer, int handPos)
{
  updateCoins(currentPlayer, state, 2);
  int i, j, k;

  for (i = 0; i < state->numPlayers; i++)
  {
    for (j = 0; j < state->handCount[i]; j++) {
      if (state->hand[i][j] == copper) {
        discardCard(j, i, state, 0);
        break;
      }
      if (j == state->handCount[i]) {
        for (k = 0; k < state->handCount[i]; k++) {
          if (DEBUG)
          printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
        }	
        break;
      }
    }
  }

  //discard played card from hand
  discardCard(handPos, currentPlayer, state, 0);			

  return 0;
}


int caGreatHall(struct gameState * state, int currentPlayer, int handPos)
{
  //+1 Card
  drawCard(handPos, state);

  //+1 Actions
  state->numActions++;

  //discard card from hand
  discardCard(handPos, currentPlayer, state, 0);

  return 0;
}


int caSeaHag(struct gameState * state, int currentPlayer) 
{
  int i;

  for (i = 0; i < state->numPlayers; i++) {
    if (i != currentPlayer){
      state->discard[i][state->discardCount[i]] = state->deck[i][state->deckCount[i]--];
      state->deckCount[i]--;
      state->discardCount[i]++;

      //Top card now a curse
      state->deck[i][state->deckCount[i]--] = curse;
    }
  }

  return 0;
}


int caSmithy(struct gameState * state, int currentPlayer, int handPos)
{
  //+3 Cards
  int i;
  for (i = 0; i < 3; i++)
  {
    drawCard(currentPlayer, state);
  }

  //discard card from hand
  discardCard(handPos, currentPlayer, state, 1);

  return 0;
}
