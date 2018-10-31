// Resizes a BMP file

#include <stdio.h>
#include <stdlib.h>
#define BITMAPOFFSET 54

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize amount infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != BITMAPOFFSET || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // create outfile BITMAPFILEHEADER and BITMAPINFOHEADER
    BITMAPFILEHEADER outBf = bf;
    BITMAPINFOHEADER outBi = bi;

      // increase the width of the BITMAPINFOHEADER biWidth by n
    int amountToIncreaseBy = atoi(argv[1]);
    outBi.biWidth *= amountToIncreaseBy;

    // increase the height of the BITMAPINFOHEADER biHeight by n
    outBi.biHeight *= amountToIncreaseBy;

    // determine padding for scanlines
    int inFilePadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outFilePadding = (4 - (outBi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // change size of BITMAPINFOHEADER biSizeImage
    outBi.biSizeImage = ((sizeof(RGBTRIPLE) * abs(outBi.biHeight) + outFilePadding) * abs(outBi.biWidth));

    // change BITMAPFILEHEADER bfSize
    outBf.bfSize = (outBi.biSizeImage + BITMAPOFFSET);

    // write outfile's BITMAPFILEHEADER
    fwrite(&outBf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&outBi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int c = 0; c < amountToIncreaseBy; c++)
        {
            // set pointer to the beginning of the scanline
            fseek(inptr, BITMAPOFFSET + (bi.biWidth * 3 + inFilePadding) * i, SEEK_SET);

            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int x = 0; x < amountToIncreaseBy; x++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            for (int k = 0; k < outFilePadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
