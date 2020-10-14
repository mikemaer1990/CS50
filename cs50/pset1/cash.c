#include <stdio.h>
#include <cs50.h>
#include <math.h>

    int main(void)
{
    // initialize variables
    float change;
    int coinCount = 0;
    // get and parse user input
    do
    {
        change = get_float("How much change?\n");
    }
    while (change <= 0);
    // convert to cents + round the number
    int cents = round(change * 100);
    // main algorithm
    do 
    {
        if ((cents - 25) >= 0)
        {
            coinCount += 1;
            cents -= 25;
        }
        else if ((cents - 10) >= 0)
        {
            coinCount += 1;
            cents -= 10;
        }
        else if ((cents - 5) >= 0)
        {
            coinCount += 1;
            cents -= 5;
        }
        else
        {
            coinCount += 1;
            cents -= 1;
        }
    }
    
    while (cents != 0);
    // print result!
    printf("Greedy Result: %i\n", coinCount);
}