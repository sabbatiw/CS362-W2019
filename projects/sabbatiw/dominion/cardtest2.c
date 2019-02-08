/*
 * tests for adventurer card effects
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define ANSI_RED   "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

#define NUM_TESTS  10
#define TEST       "adventurer"

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
 * function: test_adventurer_card
 * ------------------------------
 * test 1)  p1 hand size
 * test 2)  p1 deck size
 * test 3)  p1 discards
 * test 4)  p1 treasure
 * test 5)  p2 hand size
 * test 6)  p2 deck size
 * test 7)  p2 discards
 * test 8)  number of cards played
 * test 9)  victory card pile
 * test 10) kingdom card pile
 */

void test_adventurer_card()
{
    int i;
    int pre_treasure;
    int post_treasure;

    struct gameState Pre;
    struct gameState Post;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
                 sea_hag, tribute, smithy};

    /* prepare pre and post game states */
    initializeGame(2, k, rand() + 1, &Pre);
    memcpy(&Post, &Pre, sizeof Post);

    /* play adventurer */
    cardEffect(adventurer, 0, 0, 0, &Post, 0, 0);
  
    /* calculate treasure in hand*/
    for (i = 0, pre_treasure = 0; i < Pre.handCount[0]; i++)
    {
        int c = handCard(i, &Pre);
        if (c == copper || c == silver || c == gold) pre_treasure++;
    }
    
    for (i = 0, post_treasure = 0; i < Post.handCount[0]; i++)
    {
        int c = handCard(i, &Post);
        if (c == copper || c == silver || c == gold) post_treasure++;
    }
  
    print_line();

    /* test 1: we increase hand size +2 */
    dom_assert(Post.handCount[0], Pre.handCount[0] + 2, "p1 hand size");
    
    /* test 2 we decrease hand size -2 and also less any discards*/
    dom_assert(Post.deckCount[0], Pre.deckCount[0] - 2 - Post.discardCount[0], 
               "p1 deck size");

    /* test 3: number of discards is difference in deck count less 2 treasure */
    dom_assert(Post.discardCount[0], Pre.deckCount[0] - Post.deckCount[0] - 2, 
               "p1 discards");
    
    /* test 4: increase treasure in hand +2 */  
    dom_assert(post_treasure, pre_treasure + 2, "p1 treasure count"); 

    /* tests 5 - 7: no state change for player 2 */
    dom_assert(Post.handCount[1], Pre.handCount[1], "p2 hand size");
    dom_assert(Post.deckCount[1], Pre.deckCount[1], "p2 deck size");
    dom_assert(Post.discardCount[1], Pre.discardCount[1], "p2 discards");

    /* test 8: no cards played, because discard is not called */
    dom_assert(Post.playedCardCount, Pre.playedCardCount, "cards played");

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
    printf("                  %d of %d successful.\n",
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
    test_adventurer_card();
    
    return 0;
}
