#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define ALPHALENGTH 26
#define ASCIIA 65
#define ASCIILOWA 97


int main(int argc, string argv[])
{
    if (argc < 2 || argc > 2)
    {
        printf("You must enter one command line argument that is alphabetical. Pretty please....\n");
        return 1;
    }
    int argvLength = strlen(argv[1]);
    for (int i = 0; i < argvLength; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("You must enter one command line argument that is alphabetical. Pretty please....\n");
            return 1;
        }
    }

    string input;
    input = get_string("Enter a string to encrypt:  ");

    // get the length of the user input without stoping at the first whitespace
    int inputLength = 0; // to hold the length of the user input
    int count = 0;
    char inputChar = input[count]; // used to cycle through the user input

    while (inputChar != '\0')
    {
        inputLength++;
        count++;
        inputChar = input[count];
    }

    int alphaIndex[inputLength]; // array to hold the alphabetical index of the characters
    char result[inputLength]; // result of the cipher conversion
    int cipher[argvLength]; // array to hold the key

    // looping through the cipher key to shift characters to the alphabetical index (A or a == 0, B or b == 1, etc)
    for (int i = 0; i < argvLength; i++)
    {
        if (isupper(argv[1][i]))
        {
            cipher[i] = (int)(argv[1][i] - ASCIIA);
        }
        else
        {
            cipher[i] = (int)(argv[1][i] - ASCIILOWA);
        }
    }

    // looping throught the user input to convert the ASCII values to the alphabetical index
    int cipherCount = 0;
    for (int i = 0; i < inputLength; i++)
    {
        if (isalpha(input[i]))
        {
            if (isupper(input[i]))
            {
                alphaIndex[i] = (input[i] - ASCIIA);  // convert the ASCII value of the upper character to an alphabetical index, starting at 0
            }
            else
            {
                alphaIndex[i] = (input[i] - ASCIILOWA); // // convert the ASCII value of the lower character to an alphabetical index, starting at 0
            }

            int cipherPosition = cipherCount % argvLength;
            result[i] = (alphaIndex[i] + cipher[cipherPosition]) %
                        ALPHALENGTH; // shifting the character by the amount entered by the user
            cipherCount++;
        }
        else
        {
            result[i] = input[i];
        }
    }

    for (int i = 0; i < inputLength; i++)
    {
        if (isalpha(input[i]))
        {
            if (isupper(input[i]))
            {
                result[i] = (result[i] + ASCIIA); // convert from alphabetical index back to ASCII value
            }
            else
            {
                result[i] = (result[i] + ASCIILOWA); // convert from alphabetical index back to ASCII value
            }
        }
    }

    printf("ciphertext: ");
    for (int i = 0; i < inputLength; i++)
    {
        printf("%c", result[i]);
    }
    printf("\n");
}
