#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define CARD      "adventurer"
#define NUM_TESTS 1000

int check_adventurer_card(struct gameState *post)
{
    int i;
    int bonus;
    int discards;
    int player;
    int pre_treasure;
    int post_treasure;
    int result;

    struct gameState pre;

    bonus = 0;
    player = whoseTurn(post);

    memcpy (&pre, post, sizeof(struct gameState));

    /* play adventurer card */
    result = cardEffect(adventurer, -1, -1, -1, post, 0, &bonus);

    /* calculate treasure in hand*/
    for (i = 0, pre_treasure = 0; i < pre.handCount[player]; i++)
    {
        int c = handCard(i, &pre);
        if (c == copper || c == silver || c == gold) pre_treasure++;
    }
    
    for (i = 0, post_treasure = 0; i < post->handCount[player]; i++)
    {
        int c = handCard(i, post);
        if (c == copper || c == silver || c == gold) post_treasure++;
    }

    discards = post->discardCount[player] - pre.discardCount[player];

    if (result)
    {
        printf("\ncardEffect should return 0");
        printf("cardEffect = %d\n", result);
    }

    if (post_treasure != pre_treasure + 2)
    {
        printf("\npost_treasure == pre_treasure + 2\n");
        printf("%d != %d + 2\n", post_treasure, pre_treasure);
        result++;
    }

    if (post->handCount[player] != pre.handCount[player] + 2)
    {
        printf("\npost.handCount == pre.handCount + 2\n");
        printf("%d != %d + 2\n", post->handCount[player], pre.handCount[player]);
        result++;
    }

    if (post->deckCount[player] != pre.deckCount[player] - 2 - discards)
    {
        printf("\npost.deckCount == pre.deckCount - 2 - discards\n");
        printf("%d != %d - 2 - %d\n", post->deckCount[player], pre.deckCount[player], discards);
        result++;
    }

    return result ? 1 : 0;
}

int main ()
{
    int i;
    int j;
    int n;
    int num_treasure;
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

        G.playedCardCount      = 0;
        G.whoseTurn            = player;

        for (j = 0; j < G.handCount[player]; j++)
        {
            G.hand[player][j] = floor(Random() * 26);
        }

        do
        {
            num_treasure = 0;
            
            for (j = 0; j < G.deckCount[player]; j++)
            {
                G.deck[player][j] = floor(Random() * 26);
                if (G.deck[player][j] == copper ||
                    G.deck[player][j] == silver ||
                    G.deck[player][j] == gold)
                {
                    num_treasure++;
                }
            }

        } while (num_treasure < 2);
        
        result += check_adventurer_card(&G);
    }

    printf("\n=======\n");
    printf("results\n");
    printf("=======\n");
    printf("passed: %d\n", NUM_TESTS - result);
    printf("failed: %d\n", result);
    printf("total:  %d\n", NUM_TESTS);
    
    return 0;
}
