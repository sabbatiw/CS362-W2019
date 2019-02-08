/*
 * tests for outpost card effects
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define ANSI_RED    "\x1b[31m"
#define ANSI_GREEN  "\x1b[32m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_RESET  "\x1b[0m"

#define NUM_TESTS   10
#define TEST        "outpost"

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
 * function: test_outpost_card
 * ------------------------------
 * test 1)  outpost flag
 * test 2)  p1 hand size
 * test 3)  p1 deck size
 * test 4)  p1 discardsi
 * test 5)  p2 hand size
 * test 6)  p2 deck size
 * test 7)  p2 discards
 * test 8)  number of cards played
 * test 9)  victory card pile
 * test 10) kingdom card pile
 */

void test_outpost_card()
{
    struct gameState Pre;
    struct gameState Post;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
                 great_hall, outpost, smithy};

    /* prepare pre and post game states */
    initializeGame(2, k, rand() + 1, &Pre);
    memcpy(&Post, &Pre, sizeof Post);

    /* play outpost */
    cardEffect(outpost, 0, 0, 0, &Post, 0, 0);
     
    print_line();
    printf(ANSI_YELLOW "begin %s testing\n" ANSI_RESET, TEST);
    print_line();

    /* test 1: output flag is set +1 */
    dom_assert(Post.outpostPlayed, Pre.outpostPlayed + 1, "outpost flag");
    
    /* tests 2: decrease hand -1 after discard */
    dom_assert(Post.handCount[0], Pre.handCount[0] - 1, "p1 hand size");
    
    /* test 3: we don't draw any cards */
    dom_assert(Post.deckCount[0], Pre.deckCount[0], "p1 deck size");
    
    /* test 4: callind discardCard() does not increase this count */
    dom_assert(Post.discardCount[0], Pre.discardCount[0], "p1 discards");
    
    /* tests 5 - 7: no state change for player 2 */
    dom_assert(Post.handCount[1], Pre.handCount[1], "p2 hand size");
    dom_assert(Post.deckCount[1], Pre.deckCount[1], "p2 deck size");
    dom_assert(Post.discardCount[1], Pre.discardCount[1], "p2 discards");

    /* test 8: discardCard() is called, so we play +1 cards */
    dom_assert(Post.playedCardCount, Pre.playedCardCount + 1, "cards played");

    /* test 9: no change in victory card pile */
    dom_assert(Post.supplyCount[estate] + Post.supplyCount[duchy] + 
               Post.supplyCount[province], Pre.supplyCount[estate] + 
               Pre.supplyCount[duchy] + Pre.supplyCount[province], 
               "victory cards");

    /* test 10: no change in kingdom card pile */
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
    printf("               %d of %d successful.\n",
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
    time_t t;

    srand((unsigned) time(&t));
    test_outpost_card();
    
    return 0;
}
