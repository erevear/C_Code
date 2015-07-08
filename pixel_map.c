/*Eva Revear
TCSS 333
HW2 
This code takes two equally sized images and rearranges the pixels, or overlays them
then creates two new files with the new images*/

#include <stdio.h>
#include <stdlib.h>

/*This method takes in two files image files that have been converted to two dimensional arrays and their related size data, then blends them into one image and outputs that iimage as a file*/
void makeBlend(int height, int width, int fileSize, unsigned char imageOne[][width*3], unsigned char imageTwo[][width*3], char header[], char infoHeader[]) {
	FILE *outfile = fopen("blend.bmp", "wb");
	char blendedImage[height][width*3];
	int i, j;
	for(i = 0; i < height; i++) {
		for( j = 0; j < width*3; j++) {
			char temp = (imageOne[i][j] + imageTwo[i][j])/2;
			blendedImage[i][j] = temp;
			//printf("%x ", blendedImage[i][j]);
			//printf("\n");
		}
		
	}
	
	fwrite(header, 1, 18, outfile);
	fwrite(&height, sizeof(int), 1, outfile);
	fwrite(&height, sizeof(int), 1, outfile);
	fwrite(infoHeader, 1,  28, outfile);
	
	fwrite(blendedImage, 1, fileSize, outfile);
}


/*This method takes in two files image files that have been converted to two dimensional arrays and their related size data, then takes the images and turns them into one checkerboard image which is then output to a file*/
void makeCheckerboard(int height, int width, int fileSize, unsigned char imageOne[][width*3], unsigned char imageTwo[][width*3], char header[], char infoHeader[]) {
	FILE *outfile = fopen("checker.bmp", "wb");
	int h = 0;
	int w = 0;
	char checkerboard[height][width*3];
	int squareHeight = height/8;
	int squareWidth = (width*3)/8;
	
	int i,j;
	for(i = 0; i < 8; i++) {
		//h = i * squareHeight;
		for(j = 0; j < 8; j++) {
			w = j * squareWidth;
			if((i+j)%2 == 0) {
				h = i * squareHeight;
				for(int k = 0; k < squareHeight; k++) {
					for(int l = 0; l < squareWidth; l++) {
						checkerboard[h][w] = imageOne[h][w];
						w++;
					}
					h++;
					w = w - squareWidth;
				}
				
			}
			
			if((i+j)%2 == 1) {
				h = i * squareHeight;
				for(int k = 0; k < squareHeight; k++) {
					for(int l = 0; l < squareWidth; l++) {
						checkerboard[h][w] = imageTwo[h][w];
						w++;
					}
					h++;
					w = w - squareWidth;
				}
			}
		}
	}
	
	fwrite(header, 1, 18, outfile);
	fwrite(&height, sizeof(int), 1, outfile);
	fwrite(&height, sizeof(int), 1, outfile);
	fwrite(infoHeader, 1,  28, outfile);
	
	fwrite(checkerboard, 1, fileSize, outfile);
	
}

/*This is the main method. It asks for the names of two files, then converts those files into the data types necessary for use by the program*/
int main() {
	char fileName[20];
	char fileNameTwo[20];
	//printf("Please enter a file name");
	//scanf("%s", fileName);
	
	
	FILE *infileOne = fopen("in1.bmp", "rb");
	
	char headerOne[18];
	int fileHeightOne;
	int fileWidthOne;
	int fileSizeOne;
	char infoHeaderOne[40];
	
	//char pixelsOne[fileHeightOne][fileWidthOne*3];
	
	fread(headerOne, 1, 18, infileOne);
	fread(&fileHeightOne, sizeof(int), 1, infileOne);
	fread(&fileWidthOne, sizeof(int), 1, infileOne);
	fread(infoHeaderOne, 1, 28, infileOne);
	fseek(infileOne, 34, SEEK_SET);
	fread(&fileSizeOne, sizeof(int), 1, infileOne);
	fseek(infileOne, 54, SEEK_SET);
	unsigned char pixelsOne[fileHeightOne][fileWidthOne*3];
	//printf("%d ", fileSizeOne);
	fread(pixelsOne, 1, fileSizeOne, infileOne);
	
	//printf("Please enter a file name");
	//scanf("%s", fileNameTwo);
	
	FILE *infileTwo = fopen("in2.bmp", "rb");
	char headerTwo[18];
	int fileHeightTwo;
	int fileWidthTwo;
	int fileSizeTwo;
	char infoHeaderTwo[40];
	
	
	
	fread(headerTwo, 1, 18, infileTwo);
	fread(&fileHeightTwo, sizeof(int), 1, infileTwo);
	fread(&fileWidthTwo, sizeof(int), 1, infileTwo);
	fread(infoHeaderTwo, 1, 28, infileTwo);
	fseek(infileTwo, 34, SEEK_SET);
	fread(&fileSizeTwo, sizeof(int), 1, infileTwo);
	unsigned char pixelsTwo[fileHeightTwo][fileWidthTwo*3];
	fseek(infileTwo, 54, SEEK_SET);
	fread(pixelsTwo, 1, fileSizeTwo, infileTwo);
	
	makeCheckerboard(fileHeightOne, fileHeightTwo, fileSizeTwo, pixelsOne, pixelsTwo, headerTwo, 		infoHeaderTwo);
	
	makeBlend(fileHeightOne, fileHeightTwo, fileSizeTwo, pixelsOne, pixelsTwo, headerTwo, 		infoHeaderTwo);
	
}

