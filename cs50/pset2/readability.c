#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int endOfSentence(char letter);
int endOfWord(char letter);
int calculate(float letter, float word, float sentence);

int main(void)
{
    // prompt user for text
    string input = get_string("Text: ");
    // variable to store the length of the text
    int string_length = strlen(input);
    // initialize letter, word and sentence count;
    float letter_count = 0;
    float word_count = 0;
    float sentence_count = 0;
    // for loop to analyze the input
    for (int i = 0; i < string_length; i++)
    {
        // check if the loop is at the end of the input and increments word and sentence count
        if ((i == string_length - 1) && (!endOfSentence(input[i - 1])))
        {
            word_count++;
            sentence_count++;
        }
        // counting each letter
        else if (isalpha(input[i]))
        {
            letter_count++;
        }
        // counting each word
        else if (endOfWord(input[i]))
        {
            word_count++;
        }
        // counting each sentence
        else if (endOfSentence(input[i]))
        {
            sentence_count++;
        }

    }
    // calculate the grade level
    calculate(letter_count, word_count, sentence_count);
}
// separate function to determine if the argument (letter) is one of the three end sentence characters
int endOfSentence(char letter)
{
    if ((letter == 33) || (letter == 46) || (letter == 63))
    {
        return true;
    }
    return false;
}
// separate function to determine if the argument (letter) is a space
int endOfWord(char letter)
{
    if (isspace(letter))
    {
        return true;
    }
    return false;
}
// function to calculate the grade level
int calculate(float letter, float word, float sentence)
{
    // main calculation
    float index = 0.0588 * ((100 / word) * letter) - 0.296 * ((100 / word) * sentence) - 15.8;
    // round the result of the calculation
    int result = round(index);
    // printing results
    // below 0
    if (index <= 0)
    {
        printf("Before Grade 1\n");
        return 1;
    }
    // above 16
    else if (index >= 16)
    {
        printf("Grade 16+\n");
        return 1;
    }
    // else just print Grade + result
    printf("Grade %i\n", result);
    return 1;
}