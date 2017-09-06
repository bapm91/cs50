/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    int n = atoi(argv[1]);
    if (n <= 0 || n > 100){
        fprintf(stderr, "n, the resize factor, must be an integer.\n");
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
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    BITMAPFILEHEADER bf_new = bf;
    BITMAPINFOHEADER bi_new = bi;
    
    bi_new.biWidth = bi.biWidth * n;
    bi_new.biHeight = bi.biHeight * n;
    int padding_new = (4 - (bi_new.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bi_new.biSizeImage = abs(bi_new.biHeight) * (sizeof(RGBTRIPLE) * bi_new.biWidth + padding_new);
    bf_new.bfSize = bi_new.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);

    RGBTRIPLE *buffer = malloc(sizeof(RGBTRIPLE) * bi_new.biWidth);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        int index = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            for (int t = 0; t < n; t++){
                *(buffer + (index)) = triple;
                index++;
            }
        }
        
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
        
        for (int j = 0; j < n; j++) {
            fwrite((buffer), sizeof(RGBTRIPLE), bi_new.biWidth, outptr);
            
            for (int k = 0; k < padding_new; k++) {
                fputc(0x00, outptr);
            }
        }
    }
    free(buffer);
    fclose(inptr);
    fclose(outptr);

    // success
    return 0;
}
