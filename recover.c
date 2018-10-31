#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#define BLOCKSIZE 512

typedef __uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover file-to-recover\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inputFile = fopen(infile, "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // setting the cursor to the beginning of the file
   // fseek(inputFile, 0, SEEK_SET);


    // reading from the file
    unsigned char buffer[BLOCKSIZE];
    int numOfJPGFound = 0;
    char name[50];
    FILE *img = NULL;
    while (fread(buffer, BLOCKSIZE, 1, inputFile) == 1)
    {
        //fread(buffer, 1, BLOCKSIZE, inputFile);

        // checking the first four bytes of the buffer for the signature bytes of a JPEG
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            buffer[3] >= 0xe0 &&
            buffer[3] <= 0xef)
        {
            if (numOfJPGFound > 0)
            {
                // close the previously opened file
                fclose(img);
            }
            numOfJPGFound++;
            // print the filename
            sprintf(name, "%03i.jpg", numOfJPGFound -1);
            // create the new file
            img = fopen(name, "w");
            // write the block to the file
            fwrite(buffer, BLOCKSIZE, 1, img);
        }
            // if there is an opened file and the program hasn't reached a new JPG yet while reading
            else if (numOfJPGFound > 0)
        {
            fwrite(buffer, BLOCKSIZE, 1, img);
        }
    }
    fclose(img);
    fclose(inputFile);
}
