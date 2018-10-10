// Helper functions for music

#include <cs50.h>
#include "helpers.h"
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MIDDLEOCTAVE 4


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // converting the characters from the fraction into ints
    // https://stackoverflow.com/questions/628761/convert-a-character-digit-to-the-corresponding-integer-in-c
    char x = fraction[0];
    int numerator = x - '0';
    char y = fraction[2];
    int denominator = y - '0';

    // getting the number of eighth notes in given note
    if (denominator == 8)
    {
        return numerator;
    }
    else if (denominator == 4)
    {
        return numerator * 2;
    }
    else
    {
        return numerator * 2 * 2;
    }
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int freq = 440; // starting frequency at A440
    int octave = 0;

    // notes are formatted A4@1/4. the second char is the ocatve.
    if (strlen(note) == 2)
    {
        char x = note[1];
        octave = x - '0';
    }
    // notes with accidentals are formatted Ab4@1/4. the third char is the octave
    else if (strlen(note) == 3)
    {
        char x = note[2];
        octave = x - '0';
    }

    // setting the frequency to the A of the given octave
    while (octave < MIDDLEOCTAVE)
    {
        freq = freq / 2;
        octave++;
    }

    while (octave > MIDDLEOCTAVE)
    {
        freq = freq * 2;
        octave--;
    }

    // getting the distance from A to the other note names
    int interval = 0;
    switch (note[0])
    {
        case 'B':
            interval = 2;
            break;

        case 'C':
            interval = -9;
            break;

        case 'D':
            interval = -7;
            break;

        case 'E':
            interval = -5;
            break;

        case 'F':
            interval = -4;
            break;

        case 'G':
            interval = -2;
            break;
    }
    // adjusting the interval for any accidental
    if (strlen(note) == 3)
    {
        if (note[1] == '#')
        {
            interval++;
        }
        else if (note[1] == 'b')
        {
            interval--;
        }
    }

    if (interval < 0)
    {
        freq = round(freq / pow(2, abs(interval) / 12.0));
    }
    else if (interval > 0)
    {
        freq = round(freq * pow(2, interval / 12.0));
    }
    return freq;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s[0] == '\0')
    {
        return true;
    }
    else
    {
        return false;
    }
}