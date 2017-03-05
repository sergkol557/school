/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

const int SIZE_OF_HEADER=54;
const int SIZE_OF_BMP_INFO=40;
const int BITS_PER_PIXEL=24;
const int NO_COMPRESSION=0;
const int PARAGRAPH_WIDTH=4;
const int NEED_ARGUMENTS=3;
const WORD START_BMP=0x4d42;
const BYTE MAX_COLOR=0xff;
const BYTE MIN_COLOR=0x00;

//==================================================================================================================================
RGBTRIPLE changeColor(RGBTRIPLE color){
    if(color.rgbtRed==MAX_COLOR && color.rgbtGreen==MIN_COLOR && color.rgbtBlue==MIN_COLOR){
        color.rgbtGreen=MAX_COLOR;
        color.rgbtBlue=MAX_COLOR;
    }
    else if(color.rgbtRed!=MAX_COLOR || color.rgbtGreen!=MAX_COLOR || color.rgbtBlue !=MAX_COLOR){
        color.rgbtGreen=MIN_COLOR;
        color.rgbtBlue=MAX_COLOR;
        color.rgbtRed=MIN_COLOR;
    }    
return color;    
}
//==================================================================================================================================
int checkArguments(int argc)
{
    if (argc !=  NEED_ARGUMENTS)
        {
            fprintf(stderr, "Usage: ./copy infile outfile\n");
            return 1;
        }
    else
    {
        return 0;
    }
        
}
//==================================================================================================================================
int main(int argc, char *argv[])
{
    // ensure proper usage
    if(checkArguments(argc)!=0)
    {
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

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
    if (bf.bfType != START_BMP || bf.bfOffBits != SIZE_OF_HEADER || bi.biSize != SIZE_OF_BMP_INFO || 
        bi.biBitCount != BITS_PER_PIXEL || bi.biCompression != NO_COMPRESSION)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    //calculate total file size
    bf.bfSize=bi.biSizeImage+sizeof(bf)+sizeof(bi);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (PARAGRAPH_WIDTH - (bi.biWidth * sizeof(RGBTRIPLE)) % PARAGRAPH_WIDTH) % PARAGRAPH_WIDTH;
    
    // temporary storage
    RGBTRIPLE triple;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            //change color for algoritm
            triple=changeColor(triple);
            
            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
//==================================================================================================================================