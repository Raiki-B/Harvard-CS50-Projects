#include <cs50.h>
#include <stdio.h>

// Width of gap that is between the middle of the pyramid. The gap between the two sides.
const int gapWidth = 2;

void BuildRows(int height);
void AddCharacters(int numSpaces, char character);

int main(void)
{
    // Define height as an invalid number to start with
    int height = 0;

    // Enter do/while loop to ensure user provides valid input
    do
    {
        // Request input from the user for how tall the pyramid should be
        height = get_int("How tall should the pyramid be? \n");

        // If input is valid, then build the pyramid
        if (height > 0 && height < 9)
        {
            BuildRows(height);
        }
        else
        {
            // Input was not valid, warn user what a valid range would be.
            printf("Invalid Input. Valid input is an integer between 1 and 8.\n");
        }
    }
    while (height < 1 || height > 8);
}

/**
 * @brief Build output to the console, line by line, until it reaches specified height of pyramid.
 *
 * This will build each row of the output.
 *
 * @param height Height of pyramid.
 * @return void
 */
void BuildRows(int height)
{
    for (int i = 0; i < height; i++)
    {
        // Number of blocks and spaces for each height on the row. (e.g. for a height of 8, row 3
        // should have 5 spaces and 3 blocks.) Blocks will always be greater than 0. So at row 0, it
        // should be 1. Spaces will always be the height minus the number of blocks, to pad out the
        // length.
        int numBlocks = i + 1;
        int numSpaces = height - numBlocks;

        // Begin building the output. Start with spaces, then blocks, then a gap in the pyramid,
        // followed by the same number of blocks inverted.
        AddCharacters(numSpaces, ' ');
        AddCharacters(numBlocks, '#');
        AddCharacters(gapWidth, ' ');
        AddCharacters(numBlocks, '#');

        // End the row with a new line to start the next row - or the final line.
        printf("\n");
    }
}

/**
 * @brief Outputs specified character n number of times.
 *
 * This function takes an integer and a character as input, and will output that character to the
 * console on the same line the number of times specified.
 *
 * @param numCharacters Amount of times to print.
 * @param character Character to print.
 * @return void
 */
void AddCharacters(int numCharacters, char character)
{
    // Prints number of characters
    for (int i = 0; i < numCharacters; i++)
    {
        printf("%c", character);
    }
}
