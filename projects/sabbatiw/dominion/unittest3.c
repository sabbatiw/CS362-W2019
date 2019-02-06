#include <stdio.h>
#include "dominion.h"

#define ANSI_RED   "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

#define NUM_TESTS  5
#define TEST       "isGameOver()"

int dominion_assert(int actual, int expected)
{
    return actual == expected;
}

void test_isGameOver()
{
    int actual[NUM_TESTS];
    int count;
    int expected[NUM_TESTS];
    int i;

    struct gameState input[NUM_TESTS];

    /* set up the card supply to each have 1 card */
    for (i = 0; i < 27; i++)
    {
        input[0].supplyCount[i] = 1;
        input[1].supplyCount[i] = 1;
        input[2].supplyCount[i] = 1;
        input[3].supplyCount[i] = 1;
        input[4].supplyCount[i] = 1;
    }

    /* test 1 */
    /* no empy supply piles => game is NOT over */
    expected[0] = 0;
    
    /* test 2 */
    /* province pile is empty => game is over */
    input[1].supplyCount[province] = 0;
    expected[1] = 1;
    
    /* test 3 */
    /* < 3 piles are empty => game is NOT over */
    input[2].supplyCount[curse] = 0;
    input[2].supplyCount[estate] = 0;
    expected[2] = 0;
    
    /* test 4 */
    /* 3 piles are empty => game is over */
    input[3].supplyCount[adventurer] = 0;
    input[3].supplyCount[mine] = 0;
    input[3].supplyCount[treasure_map] = 0;
    expected[3] = 1;

    /* test 5 */
    /* > 3 piles are empty => game is over */
    input[4].supplyCount[silver] = 0;
    input[4].supplyCount[gardens] = 0;
    input[4].supplyCount[sea_hag] = 0;
    input[4].supplyCount[village] = 0;
    expected[4] = 1;

    printf("-------------------------------\n");

    count = 0;

    for (i = 0; i < NUM_TESTS; i++)
    {
        printf("%s test %d: [", TEST, i + 1);
        actual[i] = isGameOver(&input[i]);
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
    test_isGameOver();
    return 0;
}
