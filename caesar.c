/*
* CS50 PSET2
*/

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
        printf("You must enter one command line argument. Pretty please....\n");
        return 1;
    }
    else
    {
        // converting the string command line arg into an int
        int k = atoi(argv[1]);


        // getting the string to encrypt
        string input;
        input = get_string("Enter a string to encrypt:  ");

        int strLength = strlen(input); // length of the string
        int alphaIndex[strLength]; // array to hold the alphabetical index of the characters
        char result[strLength]; // result of the cipher conversion

        // looping throught the characters to convert the ASCII values to the alphabetical index
        for (int i = 0; i < strLength; i++)
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

                result[i] = (alphaIndex[i] + k) % ALPHALENGTH; // shifting the character by the amount entered by the user
            }
            else
            {
                result[i] = input[i];
            }
        }

        // converting from alphabetical index, back to the ASCII value
        for (int i = 0; i < strLength; i++)
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

        // printing the result
        printf("ciphertext: ");
        for (int i = 0; i < strLength; i++)
        {
            printf("%c", result[i]);
        }
        printf("\n");
    }
}
