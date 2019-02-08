/*
 * tests for getCost()
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
#define TEST        "getCost()"

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

void test_getCost()
{
    print_line();
    printf(ANSI_YELLOW "begin %s testing\n" ANSI_RESET, TEST);
    print_line();

    /* test 1 */
    dom_assert(getCost(0), 0, "curse");

    /* test 2 */
    dom_assert(getCost(1), 2, "estate");

    /* test 3 */
    dom_assert(getCost(2), 5, "duchy");

    /* test 4 */
    dom_assert(getCost(3), 8, "province");

    /* test 5 */
    dom_assert(getCost(4), 0, "copper");

    /* test 6 */
    dom_assert(getCost(5), 3, "silver");

    /* test 7 */
    dom_assert(getCost(6), 6, "gold");

    /* test 8 */
    dom_assert(getCost(7), 6, "adventurer");

    /* test 9 */
    dom_assert(getCost(8), 5, "council_room");

    /* test 10 */
    dom_assert(getCost(9), 4, "feast");

    /* test 11 */
    dom_assert(getCost(10), 4, "gardens");

    /* test 12 */
    dom_assert(getCost(11), 5, "mine");

    /* test 13 */
    dom_assert(getCost(12), 4, "remodel");

    /* test 14 */
    dom_assert(getCost(13), 4, "smithy");

    /* test 15 */
    dom_assert(getCost(14), 3, "village");

    /* test 16 */
    dom_assert(getCost(15), 4, "baron");

    /* test 17 */
    dom_assert(getCost(16), 3, "great_hall");

    /* test 18 */
    dom_assert(getCost(17), 5, "minion");

    /* test 19 */
    dom_assert(getCost(18), 3, "steward");

    /* test 20 */
    dom_assert(getCost(19), 5, "tribute");

    /* test 21 */
    dom_assert(getCost(20), 3, "ambassador");

    /* test 22 */
    dom_assert(getCost(21), 4, "cutpurse");

    /* test 23 */
    dom_assert(getCost(22), 2, "embargo");

    /* test 24 */
    dom_assert(getCost(23), 5, "outpost");

    /* test 25 */
    dom_assert(getCost(24), 4, "salvager");

    /* test 26 */
    dom_assert(getCost(25), 4, "sea_hag");

    /* test 27 */
    dom_assert(getCost(26), 4, "treasure_map");

    /* test 28 */
    dom_assert(getCost(27), -1, "invalid card");

    print_line();

    /* totals */
    printf("%s tests: %d of %d completed.\n", TEST, test_number, NUM_TESTS);
    printf("                 %d of %d successful.\n",
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
    test_getCost();
    
    return 0;
}
