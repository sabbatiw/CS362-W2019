#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define CARD      "outpost"
#define NUM_TESTS 10000

int check_outpost_card(struct gameState *post)
{
    int bonus;
    int player;
    int result;

    struct gameState pre;

    bonus = 0;
    player = whoseTurn(post);

    memcpy (&pre, post, sizeof(struct gameState));

    /* play outpost card */
    result = cardEffect(outpost, -1, -1, -1, post, 0, &bonus);

    if (result)
    {
        printf("\ncardEffect should return 0");
        printf("cardEffect = %d\n", result);
    }

    if (post->outpostPlayed != pre.outpostPlayed + 1)
    {
        printf("\npost.outpostPlayed == pre.outpostPlayed + 1\n");
        printf("%d != %d + 1\n", post->outpostPlayed, pre.outpostPlayed);
        result++;
    }

    if (post->handCount[player] != pre.handCount[player] - 1)
    {
        printf("\npost.handCount == pre.handCount - 1\n");
        printf("%d != %d - 1\n", post->handCount[player], pre.handCount[player]);
        result++;
    }

    if (post->discardCount[player] != pre.discardCount[player])
    {
        printf("\npost.discardCount == pre.discardCount[player]\n");
        printf("%d != %d\n", post->discardCount[player], pre.discardCount[player]);
        result++;
    }

    if (post->deckCount[player] != pre.deckCount[player])
    {
        printf("\npost.deckCount == pre.deckCount\n");
        printf("%d != %d\n", post->deckCount[player], pre.deckCount[player]);
        result++;
    }

    return result ? 1 : 0;
}

int main ()
{
    int i;
    int j;
    int n;
    int player;
    int result;

    struct gameState G;

    printf("testing %s (using random tests).\n", CARD);
    printf("=======\n");

    PlantSeeds(-1);
    SelectStream(2);

    result = 0;

    for (n = 0; n < NUM_TESTS; n++)
    {
        for (i = 0; i < sizeof(struct gameState); i++)
        {
            ((char*)&G)[i] = floor(Random() * 256);
        }

        player                 = floor(Random() * 2);
        G.deckCount[player]    = floor(Random() * (MAX_DECK - 2) + 2);
        G.discardCount[player] = floor(Random() * MAX_DECK);
        G.handCount[player]    = floor(Random() * G.deckCount[player]);
        G.outpostPlayed        = floor(Random() * (MAX_DECK - 1));

        G.playedCardCount      = 0;
        G.whoseTurn            = player;

        for (j = 0; j < G.handCount[player]; j++)
        {
            G.hand[player][j] = floor(Random() * 26);
        }

        for (j = 0; j < G.deckCount[player]; j++)
        {
            G.deck[player][j] = floor(Random() * 26);
        }

        result += check_outpost_card(&G);
    }

    printf("\n=======\n");
    printf("results\n");
    printf("=======\n");
    printf("passed: %d\n", NUM_TESTS - result);
    printf("failed: %d\n", result);
    printf("total:  %d\n", NUM_TESTS);
    
    return 0;
}
