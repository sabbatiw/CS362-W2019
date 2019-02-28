/*
 * tests for smithy card effects
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define ANSI_RED    "\x1b[31m"
#define ANSI_GREEN  "\x1b[32m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_RESET  "\x1b[0m"

#define GAME        123456789
#define NUM_TESTS   9
#define TEST        "smithy"

/*
 * global counters
 */

int test_number = 0;
int passed_tests = 0;

/*
 * function: dom_assert
 * --------------------
 * determines if two values are equal and displays the results
 */

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

/*
 * function: print_line
 * --------------------
 * prints a dashed line of 80 chars
 */

void print_line()
{
    printf("---------------------------------------" \
           "---------------------------------------\n");
}

/*
 * function: test_smithy_card
 * ------------------------------
 * test 1) p1 hand size
 * test 2) p1 deck size
 * test 3) p1 discards
 * test 4) p2 hand size
 * test 5) p2 deck size
 * test 6) p2 discards
 * test 7) number of cards played
 * test 8) victory card pile
 * test 9) kingdom card pile
 */

void test_smithy_card()
{
    struct gameState Pre;
    struct gameState Post;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
                 sea_hag, tribute, smithy};

    /* prepare pre and post game states */
    initializeGame(2, k, GAME, &Pre);
    memcpy(&Post, &Pre, sizeof Post);

    /* play smithy */
    cardEffect(smithy, 0, 0, 0, &Post, 0, 0);
    
    print_line();
    printf(ANSI_YELLOW "begin %s testing\n" ANSI_RESET, TEST);
    print_line();

    /* test 1: we increase hand size +(3 - 1) */
    dom_assert(Post.handCount[0], Pre.handCount[0] + 2, "p1 hand size");

    /* test 2: we decrease deck size -3 */
    dom_assert(Post.deckCount[0], Pre.deckCount[0] - 3, "p1 deck size");

    /* test 3: we don't discard any */
    dom_assert(Post.discardCount[0], Pre.discardCount[0], "p1 discards");

    /* tests 4-6: no state change for player 2 */
    dom_assert(Post.handCount[1], Pre.handCount[1], "p2 hand size");
    dom_assert(Post.deckCount[1], Pre.deckCount[1], "p2 deck size");
    dom_assert(Post.discardCount[1], Pre.discardCount[1], "p2 discards");

    /* test 7: we increase hand size +2 */
    dom_assert(Post.playedCardCount, Pre.playedCardCount + 1, 
            "cards played");

    /* test 8: no change in victory card pile */
    dom_assert(Post.supplyCount[estate] + Post.supplyCount[duchy] + 
               Post.supplyCount[province], Pre.supplyCount[estate] + 
               Pre.supplyCount[duchy] + Pre.supplyCount[province], 
               "victory cards");

    /* test 9: no change in kingdom card pile */
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

    /* totals */
    printf("%s tests: %d of %d completed.\n", TEST, test_number, NUM_TESTS);
    printf("              %d of %d successful.\n",
            passed_tests, NUM_TESTS);
    print_line();
}

/*
 * function: main
 * --------------
 * seed rng and run the tests
 */

int main(void)
{
    test_smithy_card();
    
    return 0;
}
