/*
 * tests for isGameOver()
 */

#include <limits.h>
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
#define NUM_TESTS   5
#define TEST        "isGameOver()"

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
  
    printf(" ] test %d (%s): expected = %d, actual = %d\n",  
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
 * function: test_whoseTurn
 * ------------------------------
 * numHandCards returns the number of cards in a player's hand
 */

void test_isGameOver()
{
    struct gameState Test;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
                 sea_hag, tribute, smithy};

    /* prepare pre and post game states */
    initializeGame(4, k, GAME, &Test);

    print_line();
    printf(ANSI_YELLOW "begin %s testing\n" ANSI_RESET, TEST);
    print_line();

    /* test 1 */
    dom_assert(isGameOver(&Test), 0, "initial");

    /* test 2 */
    Test.supplyCount[province] = 0;
    dom_assert(isGameOver(&Test), 1, "no province");
    
    /* reset */
    Test.supplyCount[province] = 1;
    
    /* test 3 */
    Test.supplyCount[adventurer] = 0;
    Test.supplyCount[embargo] = 0;
    dom_assert(isGameOver(&Test), 0, "2 empty piles");
    
    /* reset */
    Test.supplyCount[adventurer] = 1;
    Test.supplyCount[embargo] = 1;

    /* tests 4*/
    Test.supplyCount[smithy] = 0;
    Test.supplyCount[gardens] = 0;
    Test.supplyCount[tribute]= 0;
    dom_assert(isGameOver(&Test), 1, "3 empty piles");

    /* reset */
    Test.supplyCount[smithy] = 1;
    Test.supplyCount[gardens] = 1;
    Test.supplyCount[tribute] = 1;

    /* tests 5*/
    Test.supplyCount[smithy] = 0;
    Test.supplyCount[gardens] = 0;
    Test.supplyCount[treasure_map]= 0;
    dom_assert(isGameOver(&Test), 1, "3 empty piles");

    print_line();

    /* totals */
    printf("%s tests: %d of %d completed.\n", TEST, test_number, NUM_TESTS);
    printf("                    %d of %d successful.\n",
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
    test_isGameOver();
    
    return 0;
}
