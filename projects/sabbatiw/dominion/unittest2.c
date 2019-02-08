/*
 * tests for whoseTurn()
 */

#include <limits.h>
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

#define NUM_TESTS   4
#define TEST        "whoseTurn()"

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

void test_whoseTurn()
{
    struct gameState Test;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
                 sea_hag, tribute, smithy};

    /* prepare pre and post game states */
    initializeGame(4, k, rand() + 1, &Test);

    print_line();
    printf(ANSI_YELLOW "begin %s testing\n" ANSI_RESET, TEST);
    print_line();

    /* test 1 */
    dom_assert(whoseTurn(&Test), 0, "player 1");

    /* test 2 */
    Test.whoseTurn = 1;
    dom_assert(whoseTurn(&Test), 1, "player 2");

    /* test 3 */
    Test.whoseTurn = 2;
    dom_assert(whoseTurn(&Test), Test.whoseTurn, "player 3");

    /* tests 4*/
    Test.whoseTurn = 3;
    dom_assert(whoseTurn(&Test), Test.whoseTurn, "player 4");
       
    print_line();

    /* totals */
    printf("%s tests: %d of %d completed.\n", TEST, test_number, NUM_TESTS);
    printf("                   %d of %d successful.\n",
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
    test_whoseTurn();
    
    return 0;
}
