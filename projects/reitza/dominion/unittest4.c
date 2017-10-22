/* -----------------------------------------------------------------------
 * Unit test for supplyCount 
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    
    int seed = 1000;
    int numPlayer = 2;
    int p=0;
    int r, card;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine
               ,remodel, smithy, village, baron, great_hall};
    struct gameState G;
    memset(&G, 23, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, seed, &G);
    int z[]= {adventurer, council_room, feast, gardens, mine
               ,remodel, smithy, village, baron, great_hall
               ,gold, silver, copper, duchy, estate, province, curse, minion, steward};

    printf ("*****************************************\n*     TESTING supplyCount():\n*****************************************\n");

    for(card=0; card<19; card++)
    {
        printf("***Testing count for card %d\n", z[card]);
        if(G.supplyCount[z[card]]!=supplyCount(z[card],&G))
            printf("Error: supplyCount returned incorrect supply count.\n");
    }
    

    return 0;
}
