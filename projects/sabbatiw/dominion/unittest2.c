#include <limits.h>
#include <stdio.h>
#include "dominion.h"

#define ANSI_RED   "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

#define NUM_TESTS  4
#define TEST       "whoseTurn()"

int dominion_assert(int actual, int expected)
{
    return actual == expected;
}

void test_numHandCards()
{
    int actual[NUM_TESTS];
    int count;
    int expected[NUM_TESTS];
    int i;

    struct gameState input[NUM_TESTS];

    /* test 1 */
    input[0].whoseTurn = 0;
    expected[0] = 0;

    /* test 2 */
    input[1].whoseTurn = 19;
    expected[1] = 19;

    /* test 3 */
    input[2].whoseTurn = INT_MAX;
    expected[2] = INT_MAX;

    /* test 4 */
    input[3].whoseTurn = INT_MIN;
    expected[3] = INT_MIN;

    printf("-------------------------------\n");

    count = 0;

    for (i = 0; i < NUM_TESTS; i++)
    {
        printf("%s test %d: [", TEST, i);
        actual[i] = whoseTurn(&input[i]);
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
    printf("-------------------------------\n");
    printf("%d of %d tests completed.\n", i, NUM_TESTS);
    printf("%d of %d tests successful.\n", count, NUM_TESTS);
    printf("-------------------------------\n");

}

int main(void)
{
    test_numHandCards();
    return 0;
}
