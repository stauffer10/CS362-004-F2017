/* -----------------------------------------------------------------------
 * Unit test for discardCard 
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int checkDiscardCard(int handPos, int p, struct gameState *G, int trashFlag){
    
    struct gameState pre;
    int discardPreDiscard, handPreDiscard;

    memcpy (&pre, G, sizeof(struct gameState));
    discardPreDiscard = G->discardCount[p];
    handPreDiscard = G->handCount[p]; 
    
    printf("***Testing Player:%d HandCount:%d DiscardPosition:%d TrashFlag:%d***\n",p,G->handCount[p],handPos, trashFlag);    
    discardCard(handPos, p, G, trashFlag);

    if(!trashFlag && discardPreDiscard+1 != G->discardCount[p])
        printf("Error: card not added to discard pile.\n");

    if(handPreDiscard-1 != G->handCount[p])
        printf("Error: card not removed from hand.\n"); 
      
    if(!trashFlag)
    {
        //card should be removed from hand and put in trash
        pre.discard[p][pre.discardCount[p]]= pre.hand[p][handPos];
        pre.discardCount[p]++;
    }
        
    pre.hand[p][handPos] = -1;
    pre.handCount[p]--;
        
    if(handPos!=pre.handCount[p] && pre.handCount[p]!=0)
    {
        pre.hand[p][handPos] = pre.hand[p][(pre.handCount[p])];
        pre.hand[p][pre.handCount[p]] = -1;
    } 

    if(memcmp(&pre, G, sizeof(struct gameState)))
    printf("Error: indeterminate variance from expected game state.\n");

    return 0;
}

int main() {
    
    int seed = 1000;
    int numPlayer = 2;
    int p=0;
    int r;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine
               ,remodel, smithy, village, baron, great_hall};
    struct gameState G;
    memset(&G, 23, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, seed, &G);
    

    printf ("*****************************************\n*     TESTING discardCard():\n*****************************************\n");

    int i;

    for(i=0; i<3;i++)
    {
        checkDiscardCard(i,p,&G,0);
    }


    memset(&G, 23, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, seed, &G);
    

    for(i=0; i<3;i++)
    {
        checkDiscardCard(i,p,&G,1);
    }
  

    return 0;
}













