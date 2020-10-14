#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Couldn't get isdigit to work within my main function so used this instead...
bool validate(char number[]);

int main(int argc, string argv[])
{
    // Variable declarations
    int charNum;
    // Command line argument validation
    if (argc != 2)
    {
        printf("Please provide a command-line argument\n");
        return 1;
    }
    else if (validate(argv[1]))
    {
        // Caesars cipher
        string plainText = get_string("plaintext: ");
        printf("ciphertext: ");
        for (int i = 0, j = strlen(plainText); i < j; i++)
        {
            // For lower case letters that need to be wrapped around (greater than z(122))
            charNum = plainText[i] + atoi(argv[1]);
            if (charNum > 122 && islower(plainText[i]))
            {
                do
                {
                    charNum = (charNum - 122) + 96;
                }

                while (charNum > 122);
                printf("%c", charNum);
            }
            // For upper case letters that need to be wrapped around (greater than Z(90))
            else if (charNum > 90 && isupper(plainText[i]))
            {
                charNum = (charNum - 90) + 64;
                printf("%c", charNum);
            }
            // For all other characters
            else if (plainText[i] < 65 || plainText[i] > 122 || (plainText[i] > 90 && plainText[i] < 97))
            {
                charNum = charNum - atoi(argv[1]);
                printf("%c", charNum);
            }
            // For letters that don't need to be wrapped
            else
            {
                printf("%c", (plainText[i] + atoi(argv[1])));
            }
        }
        // New line and return 0 "success"
        printf("\n");
        return 0;

    }
    // If the user doesn't input a number
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;

    }
}
// Separate function to validate if character is a number or not for command line argument
// couldn't get isdigit(x) to work inside main function
bool validate(char number[])
{
    int x = 0;

    //Make sure number is not negative
    if (number[0] == '-')
    {
        x = 1;
    }
    for (; number[x] != 0; x++)
    {
        //if (number[x] > '9' || number[x] < '0')
        if (!isdigit(number[x]))
        {
            return false;
        }
    }
    return true;
}