/********************************
		 bmpToArray
Converts a windows monochrome
bitmap to a C array, starting
with height and width

By Joseph Fortune
2/19/2015
********************************/

#include <stdio.h>
#include <stdint.h>

struct BMP_File_Header
{
	uint8_t bfType[2];
	uint32_t bfSize;
	uint32_t bfReserved;
	uint32_t bfOffBits;
} __attribute__ ((__packed__));

struct BMP_Image_Header
{
	uint32_t biSize;
	uint32_t biWidth;
	uint32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
} __attribute__ ((__packed__));

int divideRoundUp(int num, int divisor)
{
	int i, quotient;
	for(i = num, quotient = 0; i > 0; i -= divisor, quotient++);
	return quotient;
}

int main(int argc, char* argv[])
{
	struct BMP_File_Header fHeader;
	struct BMP_Image_Header iHeader;
	int pixelsSize, imageSize, scanLineWidth, padding;

	if ( argc != 2 )
	{
		printf("Usage: %s <file>\n", argv[0] );
		return 0;
	}

	// Open file
	FILE *fp = fopen(argv[1], "r");
	if ( fp == NULL )
	{
		printf("Error opening file\n");
		return 0;
	}

	// Read file header
	if (fread(&fHeader , sizeof(struct BMP_File_Header), 1, fp) < 1)
	{
		printf("Error reading file\n");
		return 0;
	}

	// Validate file format
	if ( !(fHeader.bfType[0] == 'B') && (fHeader.bfType[1]) == 'M')
	{
		printf("Invalid bitmap file.\n");
		return 0;
	}

	// Read image header
	if (fread(&iHeader , sizeof(struct BMP_Image_Header), 1, fp) < 1)
	{
		printf("Error reading bmp image header\n");
		return 0;
	}

	printf("\n%s - %d x %d - %d bit(s) per pixel\n\n", argv[1], iHeader.biHeight, iHeader.biWidth, iHeader.biBitCount);

	// Verifty the bitmap is 1 bit per pixel
	if (iHeader.biBitCount != 1)
	{
		printf("Error: image must monochrome (1 bit per pixel)\n");
		return 0;
	}

	// Prepare some information for the pixels
	imageSize = divideRoundUp(iHeader.biHeight * iHeader.biWidth, 8);
	scanLineWidth = ((iHeader.biWidth / 8) / 4 + 1) * 4;
	padding = scanLineWidth - divideRoundUp(iHeader.biWidth, 8);




	// Get pixel data
	pixelsSize = iHeader.biHeight * scanLineWidth;
	uint8_t pixels[pixelsSize + 1];
	fseek(fp, fHeader.bfOffBits, SEEK_SET);
	if (fread(pixels , pixelsSize, 1, fp) < 1)
	{
		printf("Error reading pixel data\n");
		return 0;
	}

	// Print the data as a C array
	printf("char image[] = { %d, %d,\n", iHeader.biHeight, iHeader.biWidth);
	int i, j;
	for (i = 0, j = 0; i < pixelsSize; i++)
	{
			
		// Disregard null padding
		if ( !((i + padding) % scanLineWidth ))
			i += padding - 1;

		else
		{
			printf("0x%02x, ", pixels[i]);
			// New line
			j++;
			if ( j >= 10 ) // Line width
			{
				printf("\n");
				j = 0;
			}
		}
		//printf("(j: %d) ", j);
		
	}
	printf("};\n");
	
printf("Reading size: %d\n", pixelsSize);	
printf("ScanLineWidth: %d\n", scanLineWidth);
printf("Padding: %d\n", padding);
	fclose(fp);
}
