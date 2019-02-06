#include <stdio.h>
#include "dominion.h"

#define ANSI_RED   "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

#define NUM_TESTS  28
#define TEST       "getCost()"

int dominion_assert(int actual, int expected)
{
    return actual == expected;
}

void test_getCost()
{
    int actual[NUM_TESTS];
    int count;
    int expected[NUM_TESTS];
    int i;
    int input[NUM_TESTS];
    
    /* there are only 27 cards, but we are testing 28 */
    /* if a card doesn't exist, it's value should be -1 */
    for (i = 0; i < NUM_TESTS; i++)
    {
        input[i] = i;
    }

    /* test 1 */
    expected[0] = 0;
    
    /* test 2 */
    expected[1] = 2;
    
    /* test 3 */
    expected[2] = 5;
    
    /* test 4 */
    expected[3] = 8;

    /* test 5 */
    expected[4] = 0;

    /* test 6 */
    expected[5] = 3;
    
    /* test 7 */
    expected[6] = 6;
    
    /* test 8 */
    expected[7] = 6;
    
    /* test 9 */
    expected[8] = 5;

    /* test 10 */
    expected[9] = 4;

    /* test 11 */
    expected[10] = 4;
    
    /* test 12 */
    expected[11] = 5;
    
    /* test 13 */
    expected[12] = 4;
    
    /* test 14 */
    expected[13] = 4;

    /* test 15 */
    expected[14] = 3;

    /* test 16 */
    expected[15] = 4;
    
    /* test 17 */
    expected[16] = 3;
    
    /* test 18 */
    expected[17] = 5;
    
    /* test 19 */
    expected[18] = 3;

    /* test 20 */
    expected[19] = 5;

    /* test 21 */
    expected[20] = 3;
    
    /* test 22 */
    expected[21] = 4;
    
    /* test 23 */
    expected[22] = 2;
    
    /* test 24 */
    expected[23] = 5;

    /* test 25 */
    expected[24] = 4;

    /* test 26 */
    expected[25] = 4;
    
    /* test 27 */
    expected[26] = 4;
    
    /* test 28 */
    /* this card doesn't exist */
    input[27] = 27;
    expected[27] = -1;

    printf("---------------------------\n");

    count = 0;

    for (i = 0; i < NUM_TESTS; i++)
    {
        printf("%s test %d: [", TEST, i + 1);
        actual[i] = getCost(input[i]);
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
    printf("---------------------------\n");
    printf("%d of %d tests completed.\n", i, NUM_TESTS);
    printf("%d of %d tests successful.\n", count, NUM_TESTS);
    printf("---------------------------\n");

}

int main(void)
{
    test_getCost();
    return 0;
}
