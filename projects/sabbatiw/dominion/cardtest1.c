#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define ANSI_RED   "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

#define NUM_TESTS  9
#define TEST       "smithy"

int test_number = 0;
int passed_tests = 0;

void dom_assert(int actual, int expected, char *description)
{
    printf("[ ");

    if (actual == expected)
    {
        passed_tests++;
        printf(ANSI_GREEN "passed" ANSI_RESET);
    }

    else
    {
        printf(ANSI_RED "failed" ANSI_RESET);
    }
  
    printf(" ] %s test %d (%s): expected = %d, actual = %d\n", TEST, 
           ++test_number, description, expected, actual);
}

void print_line()
{
    printf("---------------------------------------" \
           "---------------------------------------\n");
}

void test_smithy_card()
{
    struct gameState Pre;
    struct gameState Post;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
                 sea_hag, tribute, smithy};

    initializeGame(2, k, rand() + 1, &Pre);
    memcpy(&Post, &Pre, sizeof Post);
    cardEffect(smithy, 0, 0, 0, &Post, 0, 0);
    
    print_line();

    dom_assert(Post.handCount[0], Pre.handCount[0] + 2, "p1 hand size");
    dom_assert(Post.deckCount[0], Pre.deckCount[0] - 3, "p1 deck size");
    dom_assert(Post.discardCount[0], Pre.discardCount[0], "p1 discards");

    dom_assert(Post.handCount[1], Pre.handCount[1], "p2 hand size");
    dom_assert(Post.deckCount[1], Pre.deckCount[1], "p2 deck size");
    dom_assert(Post.discardCount[1], Pre.discardCount[1], "p2 discards");

    dom_assert(Post.playedCardCount, Pre.playedCardCount + 1, 
            "cards played");

    dom_assert(Post.supplyCount[estate] + Post.supplyCount[duchy] + 
               Post.supplyCount[province], Pre.supplyCount[estate] + 
               Pre.supplyCount[duchy] + Pre.supplyCount[province], 
               "victory cards");

    dom_assert(Post.supplyCount[k[0]] + Post.supplyCount[k[1]] + 
               Post.supplyCount[k[2]] + Post.supplyCount[k[3]] +
               Post.supplyCount[k[4]] + Post.supplyCount[k[5]] +
               Post.supplyCount[k[6]] + Post.supplyCount[k[7]] +
               Post.supplyCount[k[8]] + Post.supplyCount[k[9]],
               Pre.supplyCount[k[0]] + Pre.supplyCount[k[1]] +
               Pre.supplyCount[k[2]] + Pre.supplyCount[k[3]] +
               Pre.supplyCount[k[4]] + Pre.supplyCount[k[5]] +
               Pre.supplyCount[k[6]] + Pre.supplyCount[k[7]] +
               Pre.supplyCount[k[8]] + Pre.supplyCount[k[9]], "kingdom cards");
    
    print_line();
    printf("%s tests: %d of %d completed.\n", TEST, test_number, NUM_TESTS);
    printf("              %d of %d successful.\n",
            passed_tests, NUM_TESTS);
    print_line();
}

int main(void)
{
    time_t t;

    srand((unsigned) time(&t));
    test_smithy_card();
    return 0;
}
