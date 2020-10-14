#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
// Initiate validation function
bool validate(string str);
// Main function
int main(int argc, string argv[])
{
    // Create alphabet array
    char alphabet[26];
    for (int i = 0; i < 26; i++)
    {
        alphabet[i] = (char)(i + 65);
    }
    // Validate that the user input only one argument
    if (argc != 2)
    {
        printf("Please provide a command-line argument\n");
        return 1;
    }
    // Validate the length and content of the argument
    else if (!validate(argv[1]))
    {
        return 1;
    }
    // Main body of function
    else
    {
        // Get the text to translate
        string plainText = get_string("plaintext: ");
        // Print ciphertext header
        printf("ciphertext: ");
        // Loop through each letter in the "plaintext" input
        for (int j = 0, y = strlen(plainText); j < y; j++)
        {
            // Don't translate spaces or other characters
            if (!isalpha(plainText[j]))
            {
                printf("%c", plainText[j]);
            }
            // Find each letter of the users input and match its according index number in the alphabet
            for (int t = 0; t < 26; t++)
            {
                // For lowercase letters
                if (islower(plainText[j]))
                {
                    if (toupper(plainText[j]) == alphabet[t])
                    {
                        // Print the letter that matches the same index in the cipher alphabet as the users input character
                        printf("%c", tolower(argv[1][t]));
                    }

                }
                // Same thing for uppercase letters
                else if (isupper(plainText[j]))
                {
                    if (plainText[j] == alphabet[t])
                    {
                        printf("%c", toupper(argv[1][t]));
                    }
                }
            }
        }
        // Print a new line after program is complete and return 0
        printf("\n");
        return 0;
    }
}

// Separate function to validate length and content of input cipher alphabet
bool validate(string str)
{
    // If provided alphabet is not 26 characters long return false
    if (strlen(str) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }
    // If two identical characters are found return false
    for (int i = 0, j = strlen(str) - 1; i < j; i++)
    {
        for (int k = i + 1, l = strlen(str); k < l; k++)
        {
            if (str[i] == str[k] || !isalpha(str[i]))
            {
                printf("Key must contain 26 unique alphabetical characters.\n");
                return false;
            }
        }
    }
    // Return true if no dupes found
    return true;
}