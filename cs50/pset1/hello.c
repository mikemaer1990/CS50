#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Asks user for their name
    string name = get_string("What is your name? ");
    // Output is hello + their name.
    printf("hello, %s\n", name);
}