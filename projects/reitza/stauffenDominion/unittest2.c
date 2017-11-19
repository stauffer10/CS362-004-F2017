/* -----------------------------------------------------------------------
 * Unit test for gainCard
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

int checkGainCard(int supplyPos, struct gameState *G, int toFlag, int p){
    
    struct gameState pre;
    memcpy (&pre, G, sizeof(struct gameState));
    int r;

    
    //printf("***Testing Player:%d supplyPos:%d toFlag:%d ***\n",p,supplyPos,toFlag);    
    r = gainCard(supplyPos,G,toFlag,p);

    if(pre.supplyCount[supplyPos]<=0)
    {
        if(r!=-1)
            printf("Error: supply was empty but function didn't return -1\n");
        else
            return 0;
    }

    if(toFlag==0)//discard
    {
        pre.discard[p][pre.discardCount[p]] = supplyPos;
        pre.discardCount[p]++;
        if(pre.discard[p][pre.discardCount[p]]!=G->discard[p][G->discardCount[p]])
        {
            printf("Error: card not correctly added to discard pile\n");
        }
        if(pre.discardCount[p]!=G->discardCount[p])
        {
            printf("Error: discard count not changed correctly\n");
        }
    }
    else if(toFlag==1)//deck
    {
        pre.deck[p][pre.deckCount[p]] = supplyPos;
        pre.deckCount[p]++;
        if(pre.deck[p][pre.deckCount[p]]!=G->deck[p][G->deckCount[p]])
        {
            printf("Error: card not correctly added to deck\n");
        }
        if(pre.deckCount[p]!=G->deckCount[p])
        {
            printf("Error: deck count not changed correctly\n");
        }
    }
    else if(toFlag==2)//hand
    {
        pre.hand[p][pre.handCount[p]] = supplyPos;
        pre.handCount[p]++;
        if(pre.hand[p][pre.handCount[p]]!=G->hand[p][G->handCount[p]])
        {
            printf("Error: card not correctly added to hand\n");
        }
        if(pre.handCount[p]!=G->handCount[p])
        {
            printf("Error: hand count not changed correctly\n");
        }
    }

    pre.supplyCount[supplyPos]--;

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
    //memset(&G, 23, sizeof(struct gameState));
    //r = initializeGame(numPlayer, k, seed, &G);
    int z[5] = {adventurer, smithy, estate, gold, curse};

    printf ("*****************************************\n*     TESTING gainCard():\n*****************************************\n");

    int i,player,c,flag;

    for(flag=0;flag<3;flag++)
    {
        for(player=0; player<2; player++)
        {
            memset(&G, 23, sizeof(struct gameState));
            r = initializeGame(numPlayer, k, seed, &G);

            for(c=0;c<5;c++)
            {
                printf("***Testing Player:%d supplyPos:%d toFlag:%d ***\n",player,z[c],flag);
                for(i=0;i<11;i++)
                {
                    checkGainCard(z[c], &G, flag, player);
                }
            }
        }
    }

    return 0;
}













