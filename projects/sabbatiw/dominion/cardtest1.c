#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"

#define ANSI_RED   "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

#define NUM_TESTS  4
#define TEST       "smithy card"

int dominion_assert(int actual, int expected)
{
    return actual == expected;
}

void test_smithy_card()
{
    int actual[NUM_TESTS];
    int count;
    int expected[NUM_TESTS];
    int i;
    int input[NUM_TESTS];

    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

//    initializeGame(2, k, 1, &G);

    /* test 1 */
    input[0] = 3;
    expected[0] = input[0] + 2;

    /* test 2 */
    input[1] = 8;
    expected[1] = input[1] + 2;

    /* test 3 */
    input[2] = 0;
    expected[2] = input[2] + 2;

    /* test 4 */
    input[3] = -2;
    expected[3] = input[3] + 2;

    printf("----------------------------\n");

    count = 0;

    for (i = 0; i < NUM_TESTS; i++)
    {
        initializeGame(2, k, rand() + 1, &G);

        G.handCount[0] = input[i];

        printf("%s test %d: [", TEST, i + 1);
        play_smithy(&G, 0);
        actual[i] = G.handCount[0];
        if (dominion_assert(actual[i], expected[i]))
        {
            count++;
            printf(ANSI_GREEN "passed" ANSI_RESET "]\n");
        }
        
        else
        {
            printf(ANSI_RED "failed" ANSI_RESET "] expected value: ");
            printf("%d, actual value: %d\n", expected[i], actual[i]);
        }
    }

    printf("----------------------------\n");
    printf("%d of %d tests completed.\n", i, NUM_TESTS);
    printf("%d of %d tests successful.\n", count, NUM_TESTS);
    printf("----------------------------\n");

}

int main(void)
{
    time_t t;

    srand((unsigned) time(&t));
    test_smithy_card();
    return 0;
}
