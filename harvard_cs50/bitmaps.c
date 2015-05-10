// Problem Set 5 - Enlarging Bitmaps

/****************************************************************************
 * enlarge.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Enlarges a BMP file by a factor of [n].
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


int
main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: enlarge n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];


    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
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
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // save original neccesary bitmap metadata
    int old_height = bi.biHeight;
    int old_width = bi.biWidth;
    int old_padding =  (4 - (old_width * sizeof(RGBTRIPLE)) % 4) % 4;

    // update bitmap metadata
    bi.biWidth *= n;
    bi.biHeight *= n;
    bf.bfSize = 14 + 40 + abs(bi.biWidth * bi.biHeight * 3);
    bi.biSizeImage = abs(bi.biWidth * bi.biHeight * 3);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines

    RGBTRIPLE *buffer = malloc(sizeof(RGBTRIPLE) * bi.biWidth);

    int i;
    for (i = 0, old_height = abs(old_height); i < old_height; i++)
    {
        int element = 0;
        for (int j = 0; j < old_width; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile (scaled by [n])
            for(int scale = 0; scale < n; scale++, element++) {
                buffer[element] = triple;
            }
        }

        // skip over padding, if any
           fseek(inptr, old_padding, SEEK_CUR);

        for(int scale = 0; scale < n; scale++) {
            fwrite(buffer, sizeof(RGBTRIPLE), bi.biWidth, outptr);
              }

        // write padding to outfile
           for (int k = 0; k < padding; k++)
            fputc(0x00, outptr);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
