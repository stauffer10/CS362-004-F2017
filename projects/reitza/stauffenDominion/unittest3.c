/* -----------------------------------------------------------------------
 * Unit test for whoseTune 
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
    int numPlayer = 4;
    int p=0;
    int r;
    
    int k[10] = {adventurer, council_room, feast, gardens, mine
               ,remodel, smithy, village, baron, great_hall};
    struct gameState G;
    memset(&G, 23, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, seed, &G);
    

    printf ("*****************************************\n*     TESTING whoseTurn():\n*****************************************\n");

    for(p=0; p<4;p++)
    {
        printf("***Testing Player %d's turn\n",p);
        if(G.whoseTurn != whoseTurn(&G))
            printf("Error: whoseTurn returned incorrect player number.\n");
        G.whoseTurn++;
    }
    return 0;
}
