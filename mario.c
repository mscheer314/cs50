#include <stdio.h>
#include <cs50.h>

// TODO: remove trailing whitespace from each line. ex: " #  # " - the last space needs to go. should be " #  #"

void printRow(int, int);

int main(void)
{
    int height; // holds the user input

    // ask repeatedly until a valid input is given
    do
    {
        height = get_int("Give a pyramid height (max height 23): ");
    }
    while (height < 0 || height > 23);

    //print the pyramid
    for (int i = height; i > 0; i--)
    {
        printRow(height, i);
    }
}

void printRow(int height, int level) // takes the pyramid height and the level that is being printed
{
    int l = level; // level of the pyramid being printed
    int j = level;


    // prints the rows

    // prints the left side of the double pyramid
    for (int i = 0; i < height; i++)   // cycle through every spot on the level
    {
        if (l > 1)
        {
            if (1 < l)
            {
                printf(" ");
            }
            l--;
        }
        else
        {
            printf("#");
        }
    }

    printf("  ");  // prints the space between the half pyramids

    // prints the right side of the double pyramid
    for (int i = height; i > 0; i--)
    {
        if (j - i <= 0)
        {
            printf("#");
        }
        /*else
        {
            printf("#");
        }*/
    }
    printf("\n");
}
