/*
* CS50 PSET1
*/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long long credNum;
    int countDigit(long long n);

    // get user input and validate that it is a good credit card number
    credNum = get_long_long("Please enter a credit card number to check (without any spaces or dashes): ");

    if (credNum < 1000000000000 || credNum > 9999999999999999)
    {
        printf("INVALID\n");
    }
    else
    {
        int x; //  for storing every other digit of the credit card
        int checkSum = 0;  // checksum

        // looping to get every other digit in the credit card number
        for (long i = 10; i < 10000000000000000; i = i * 100)
        {
            x = (credNum / i) % 10; // x is now the digit desired
            //printf("%d\n", x);

            if ((x * 2) < 10)   // checking if the digit * 2 is two digits long
            {
                checkSum = checkSum + (x * 2);  // adding that digit * 2 to the checkSum
            }
            else
            {
                checkSum = checkSum + ((x * 2) % 10) + ((x * 2) / 10);   //  adding the first digit of x * 2 to the second digit
            }
        }

        // looping to add the remaining digits to the y sum (every other starting with the first)
        for (long i = 1; i < 10000000000000000; i = i * 100)
        {
            x = credNum / i % 10; // gets the first digit of the credit card
            checkSum = checkSum + x;   // adds the digit to the total
        }


        // now checking the credit card number is valid

        if ((checkSum % 10) != 0)  // checksum must end in 0 to be vaild credit card number
        {
            printf("INVALID\n");
        }
        else
        {
            // checking for AMEX (15 digits, starts with 34 or 37)
            if (countDigit(credNum) == 15)
            {
                if ((credNum / 10000000000000) == 34 || (credNum / 10000000000000) == 37) // checking first two digits for 34 or 37
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else if (countDigit(credNum) == 16)
            {
                if ((credNum / 100000000000000) > 50 && (credNum / 100000000000000) < 56) // checking first two digits for 51 - 55
                {
                    printf("MASTERCARD\n");
                }
                else if ((credNum / 1000000000000000) == 4)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else if (countDigit(credNum) == 13)
            {
                if ((credNum / 1000000000000) == 4)
                {
                    printf("VISA");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
        }
    }
}




int countDigit(long long n)
{
    int count = 0;
    while (n != 0)
    {
        n = n / 10;
        ++count;
    }
    return count;
}
