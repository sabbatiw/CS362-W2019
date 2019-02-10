#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* this is the magic string we're looking for */
static char random_string[] = "reset";

/*
 * function: inputChar
 * -------------------
 * returns a random character from input_pool[].
 */

char inputChar()
{
    char input_pool[] = "[({ ax})]";
    return input_pool[rand() % strlen(input_pool)];
}

/*
 * function: inputString
 * ---------------------
 * returns a random string using the characters from input_pool[]. the size of
 * the string is always the same size as the globally defined random_string[].
 */

char *inputString()
{
    int i;
    char input_pool[] = "erst";
    
    for (i = 0; i < (int)strlen(random_string); i++)
    {
        random_string[i] = input_pool[rand() % strlen(input_pool)];
    }
    
    return random_string;
}

void testme()
{
    int tcCount = 0;
    char *s;
    char c;
    int state = 0;
    
    while (1)
    {
        tcCount++;
        c = inputChar();
        s = inputString();
        
        printf("Iteration %d: c = %c, s = %s, state = %d\n", 
                tcCount, c, s, state);
        
        if (c == '[' && state == 0) state = 1;
        if (c == '(' && state == 1) state = 2;
        if (c == '{' && state == 2) state = 3;
        if (c == ' ' && state == 3) state = 4;
        if (c == 'a' && state == 4) state = 5;
        if (c == 'x' && state == 5) state = 6;
        if (c == '}' && state == 6) state = 7;
        if (c == ')' && state == 7) state = 8;
        if (c == ']' && state == 8) state = 9;
        
        if (s[0] == 'r' && s[1] == 'e'
                && s[2] == 's' && s[3] == 'e'
                && s[4] == 't' && s[5] == '\0'
                && state == 9)
        {
            printf("error ");
            exit(200);
        }
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    
    return 0;
}
