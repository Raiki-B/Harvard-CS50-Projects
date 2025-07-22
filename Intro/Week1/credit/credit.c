#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define VISA_LEN_SHORT 13
#define AMEX_LEN 15
#define CARD_LEN_LONG 16

long ExtractDigit(long input, size_t place);
size_t GetLongLength(long input);
bool VerifyChecksum(const int digits[], size_t length);
string CheckCard(long cardNumber);

int main()
{
    long input = 4003600000000014;

    // Prompt user for input of a credit card number
    long ccn = get_long("Enter credit card number: \n");

    // Check card number, and print result representing the type of card it is, with type INVALID
    // representing an invalid card.
    printf("%s\n", CheckCard(ccn));
}

/**
 * @brief Determines the credit card type based on number and checksum.
 *
 * This function analyzes the credit card number's length and starting digits
 * to classify it as VISA, MASTERCARD, AMEX, or INVALID.
 * It also checks whether the card number passes a Luhn checksum.
 *
 * @param cardNumber The full credit card number to check.
 * @return A string representing the card type ("VISA", "MASTERCARD", "AMEX", or "INVALID").
 */
string CheckCard(long cardNumber)
{
    // Get length of card number
    size_t ccnLength = GetLongLength(cardNumber);

    // Build digit array of card number digits for easier access
    int ccnDigits[ccnLength];
    for (int i = 0; i < ccnLength; i++)
    {
        // Get digit at place i+1
        ccnDigits[i] = ExtractDigit(cardNumber, i + 1);
    }

    // Default to INVALID card type, if no checks match, then it will be invalid by default.
    string cardType = "INVALID";

    // Only VISA cards can be 13 digits long, so check if it is 13 digits in length and also starts
    // with a 4.
    if (ccnLength == VISA_LEN_SHORT && ccnDigits[ccnLength - 1] == 4)
    {
        cardType = "VISA";
    }

    // Only AMEX cards can be 15 digits long, so check if it is 15 digits in length and if the
    // digits start with 34 or 37.
    else if (ccnLength == AMEX_LEN && ccnDigits[ccnLength - 1] == 3 &&
             (ccnDigits[ccnLength - 2] == 4 || ccnDigits[ccnLength - 2] == 7))
    {
        cardType = "AMEX";
    }

    // Both VISA and MasterCard can be 16 digits in length, so break into multiple if statements
    // after.
    else if (ccnLength == CARD_LEN_LONG)
    {
        // VISA cards will start with digit 4. If it does, then it's a VISA card.
        if (ccnDigits[ccnLength - 1] == 4)
        {
            cardType = "VISA";
        }
        // MasterCard cards will start with 51, 52, 53, 54, or 55.
        else if (ccnDigits[ccnLength - 1] == 5 &&
                 (ccnDigits[ccnLength - 2] > 0 && ccnDigits[ccnLength - 2] < 6))
        {
            cardType = "MASTERCARD";
        }
    }
    // No else case needed as card type defaults to INVALID.

    // If card was not found as INVALID via previous steps, then verify checksum of card.
    if (strcmp(cardType, "INVALID") != 0)
    {
        bool validChecksum = VerifyChecksum(ccnDigits, ccnLength);
        if (!validChecksum)
        {
            // Not a valid checksum, therefore set card type back to invalid.
            cardType = "INVALID";
        }
    }

    // Finally, return the type of the card as per course instructions.
    return cardType;
}

/**
 * @brief Verifies the checksum of a credit card number using the Luhn algorithm.
 *
 * This function calculates the checksum of the digits in a credit card number
 * and returns whether it passes validation.
 *
 * @param digits An array of digits in the credit card number (in reverse order).
 * @param length The number of digits in the array.
 * @return true if the checksum is valid, false otherwise.
 */
bool VerifyChecksum(const int digits[], size_t length)
{
    int a = 0; // Sum of digits at even indices from the right
    int b = 0; // Sum of digits at odd indices from the right

    // Begin iterating through each digit of the card number, adding them to the sum of a or b
    // respective of whether it is an even or odd indice from the right.
    for (int i = 0; i < length; i++)
    {
        // Even Indices
        if (i % 2 == 0)
        {
            a += digits[i];
        }

        // Odd Indices
        else
        {
            int c = digits[i] * 2; // Temporary variable to store the result while we work with it.
            if (c < 10)
            {
                // Result is single digit, simple and easy to work with, just add to the sum.
                b += c;
            }
            else
            {
                // Result is two digits, we need to seperate out the digits and add them to the sum
                // seperately.
                b += c / 10;
                b += c % 10;
            }
        }
    }

    // Finally, if the final digit is 0, return true. Else, return false. 20%10=0 would be true,
    // whereas 17%10=7 would be false.
    return (a + b) % 10 == 0;
}

/**
 * @brief Extracts a single digit from a number at a specific place.
 *
 * Gets the digit at a specified place, counting from the right (1-based index).
 * For example, ExtractDigit(1234, 2) returns 3.
 *
 * @param input The number to extract the digit from.
 * @param place The place of the digit (1 = rightmost digit).
 * @return The digit at the specified place.
 */
long ExtractDigit(long input, size_t place)
{
    long l;

    // Modulo of input%(10^place), for example if you passed 1234 as the input with 2 as the place,
    // it would result in 1234%100=17
    l = input % (long) pow(10, place);

    // In the previous comment, the result would be 17. We don't want the 7 digit, so we need to
    // strip it. We do this by using the same formula, but for the previous digit, and subtracting
    // the result. This would set the variable to 10.
    l -= input % (long) pow(10, place - 1);

    // Again, 10 isn't the number we want, that's 2 digits. We just want the single digit (1)
    // representing the tenth place. So, we need to divide it by the place it is in. (e.g. 10/10=1)
    l /= (long) pow(10, place - 1);

    // Finally, return the result.
    return l;
}

/**
 * @brief Calculates the number of digits in a given number.
 *
 * Uses division by 10 to count how many digits are in the input number.
 *
 * @param input The number whose digit length is to be calculated.
 * @return The number of digits in the input.
 */
size_t GetLongLength(long input)
{
    size_t length = 0;
    long workingInput = input;

    // Continuously divide by 10 until the number reaches 0, iterating length each time it divides
    // by 10.
    do
    {
        workingInput /= 10;
        length++;
    }
    while (workingInput != 0);

    // Finally, return the length result, now that we have finished dividing by 10.
    return length;
}
