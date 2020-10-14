#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    // Asks user for the desired height
    
    do
    {
        height = get_int("Height: ");
    }
    // Parse input
    while (height <= 0 || height > 8);
    
    for (int i = 0; i < height; i++) 
    {
        // Add white space
        for (int u = height - (i + 1); u > 0; u--) 
        {
            printf(" ");
        }
        // Print hashes (j times)
        for (int j = 0; j <= i; j++) 
        {
            printf("#");
        }
        // middle spaces
        printf("  ");
        // right side of pyramid
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("\n"); 
    }
}