#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // Variable declarations
    int last, first, firstTwo, count, length, multiply, digit0, digit, digit1, luhnTotal, test;
    long cc, ccCopy, ccCopy1;
    int multSum = 0;
    int addSum = 0;
    // Variable initializations
    cc = get_long("Enter your credit card number: \n");
    length = log10(cc) + 1;
    count = log10(cc);
    first =  cc / pow(10, count);
    firstTwo = cc / pow(10, count - 1);
    ccCopy = cc;
    ccCopy1 = cc;

    // Luhn Stage #1
    for (int i = length - 1; i >= 0; i -= 2)
    {
        digit = (ccCopy / 10) % 10;
        digit0 = digit * 2;

        test = log10(digit0);

        if (test == 1)
        {
            digit = (digit0 % 10) + ((digit0 / 10) % 10);
            multSum += digit;
            ccCopy /= 10;
            ccCopy /= 10;
        }
        else
        {
            multSum += (digit * 2);
            ccCopy /= 10;
            ccCopy /= 10;
        }
    }
    // Luhn Stage #1a
    for (int j = length - 1; j >= 0; j -= 2)
    {
        digit1 = ccCopy1 % 10;
        addSum += digit1;
        ccCopy1 /= 10;
        ccCopy1 /= 10;
    }
    // Luhn Stage #2
    luhnTotal = addSum + multSum;
    // If CC passes Luhn's Algorithm -- then get the card type!
    if (luhnTotal % 10 == 0)
    {
        if (((firstTwo == 34) || (firstTwo == 37)) && (length == 15))
        {
            printf("AMEX\n");
        }
        else if ((first == 4) && ((length == 13) || (length == 16)))
        {
            printf("VISA\n");
        }
        else if (((firstTwo == 51) || (firstTwo == 52) || (firstTwo == 53) || (firstTwo == 54) || (firstTwo == 55)) && length == 16)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
