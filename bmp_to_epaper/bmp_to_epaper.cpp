
#include "stdafx.h"
#include "windows.h"
#include "ModuleType.h"


//Set to 1 for a one dimensional array. Set to 0 for the more conventional
//2-dimensional array.
#define ONE_DIM (1)
Module enteredModule;

//
//===========================================================================
std::string getOutputFile(const char *path)
{
	std::string
		myPath;
	char
		drive[_MAX_DRIVE];
	char
		dir[_MAX_DIR];
	char
		fname[_MAX_FNAME];
	char
		ext[_MAX_EXT];

	_splitpath_s(path, drive, dir, fname, ext );

	myPath = drive;
	myPath += dir;
	myPath += fname;
	myPath += ".h";

	return myPath;
}
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
  {
  FILE
   *filePtr;
  BITMAPFILEHEADER
    bitmapFileHeader;

  //We will allocate memory for the bitmap, image data at this pointer.
  unsigned char
   *bitmapImage;
  size_t
    bytes_read_from_bitmap;
  errno_t
    file_open_err;

  //open filename in read binary mode
  file_open_err=fopen_s(&filePtr,filename,"rb");
  if(file_open_err)
    {
	printf("Error# %d: %s reading the BMP in: \"%s\"\n",file_open_err,strerror(file_open_err), filename);
	return(NULL);
    }

  //read the bitmap file header
  fread(&bitmapFileHeader,sizeof(BITMAPFILEHEADER),1,filePtr);

  //verify that this is a bmp file by check bitmap id
  if(0x4D42 != bitmapFileHeader.bfType)
    {
    fclose(filePtr);
    return(NULL);
    }

  //read the bitmap info header
  fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr);

  //move file point to the begining of bitmap data
  fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

  int imageSize = bitmapInfoHeader->biHeight*bitmapInfoHeader->biWidth * 3;

  //allocate enough memory for the bitmap image data
  bitmapImage = (unsigned char*)malloc(imageSize);


  //verify memory allocation
  if (NULL == bitmapImage)
  {
    fclose(filePtr);
    return(NULL);
  }

  //read in the bitmap image data
  bytes_read_from_bitmap =
    fread(bitmapImage, 1, imageSize, filePtr);

  //make sure bitmap image data was read
  if (bytes_read_from_bitmap != imageSize)
  {
    free(bitmapImage);
    fclose(filePtr);
    return(NULL);
  }

  //We are only set up to do 24 bit BMPs, which are
  //more or less standard.
  if (bitmapInfoHeader->biBitCount != 24)
  {
    free(bitmapImage);
    fclose(filePtr);
    return(NULL);
  }

  //close file
  fclose(filePtr);
  //return bitmap image data
  return(bitmapImage);
}

//===========================================================================
void usage(char *our_name)
  {
  printf("Usage:\n");
  printf("  %s [infile]\n", our_name);
  printf("  [infile] is 24-bit BMP\n");
  printf("  This application will generate a c based header file for Gray 2BPP and Red 1BPP packed source\n");
  }
//===========================================================================
int main(int argc, char*  argv[])
{
	//argv[0] = program location
	//argv[1] = bmp
	//argv[2] = CFA ePaper PN

	BITMAPINFOHEADER
		bitmapInfoHeader;
	unsigned char
		*bitmapData;


	//Must have 3 parameters including path
	if (3 != argc)
	{
		usage(argv[0]);
		printf("Incorrect number of arguments entered");
		return(1);
	}


	//set the parameters of the module for the entered CFA PN
	enteredModule.setModuleType(argv[2]);
	//enteredModule.setModuleType("Wrong");
	
	char *sourceFile = argv[1];
	std::string outputFile = getOutputFile(argv[1]);

	printf("Reading input bitmap: %s\n", argv[1]);
	//Crack open the BMP, and read the image data
	bitmapData = LoadBitmapFile(argv[1], &bitmapInfoHeader);

	//Check that the operation went OK.
	if (NULL == bitmapData)
	{
		printf("Error reading/processing the BMP.\n");
		system("pause");
		usage(argv[0]);
		return(1);
	}

	printf("biWidth = %d\n", bitmapInfoHeader.biWidth);
	printf("biHeight = %d\n", bitmapInfoHeader.biHeight);
	printf("biBitCount = %d\n", bitmapInfoHeader.biBitCount);

	//check to make sure the pixel width of the image matches the screen width
	if (enteredModule.getWidth() != bitmapInfoHeader.biWidth)
	{
		printf("Pixel width of %d is not allowed for this module, image must be %d pixels wide.",bitmapInfoHeader.biWidth,enteredModule.getWidth());
		while (1);
	}

	//check to make sure the pixel height of the image matches the screen height
	if (enteredModule.getLength() != bitmapInfoHeader.biHeight)
	{
		printf("Height of %d pixels is not allowed for this module, image must be %d pixels in height.", bitmapInfoHeader.biHeight, enteredModule.getLength());
		while (1);
	}


	//We are only set up to do 24 bit BMPs, which are
	//more or less standard.
	if (24 != bitmapInfoHeader.biBitCount)
	{
		printf("This  program  can  only  process  24  bit  BMPs, the  input  BMP  is  %d\n",
			bitmapInfoHeader.biBitCount);
		usage(argv[0]);
		//free  the  memory  allocated  by  LoadBitmapFile
		free(bitmapData);
		return(1);
	}

	errno_t
		file_open_err;
	FILE
		*Grey_2bit_and_Red_1bit_out;

	file_open_err = fopen_s(&Grey_2bit_and_Red_1bit_out, outputFile.c_str(), "wt");
	if (file_open_err)
	{
		printf("Error# %d: %s opening the 2bpp grey + 1bpp red output file: \"%s\"\n", file_open_err, strerror(file_open_err), outputFile.c_str());
		usage(argv[0]);
		//free the memory allocated by LoadBitmapFile
		free(bitmapData);
		//Indcicate failure, exit
		return 0;
	}
	printf("Opened \"%s\" as the 2bpp grey + 1bpp red output file.\n", outputFile.c_str());

	//The output file is open. Write out the header information to the grey file.

	fprintf(Grey_2bit_and_Red_1bit_out, "//Source image file: \"%s\"\n", argv[1]);
	fprintf(Grey_2bit_and_Red_1bit_out, "#define HEIGHT_PIXELS    (%d)\n", bitmapInfoHeader.biHeight);
	fprintf(Grey_2bit_and_Red_1bit_out, "#define WIDTH_PIXELS     (%d)\n", bitmapInfoHeader.biWidth);
if(enteredModule.getGBits() == 2)
	fprintf(Grey_2bit_and_Red_1bit_out, "#define WIDTH_GREY_BYTES (%d)\n", (bitmapInfoHeader.biWidth + 0x03) >> 2);

if(enteredModule.getRBits() == 1)
	fprintf(Grey_2bit_and_Red_1bit_out, "#define WIDTH_RED_BYTES  (%d)\n", (bitmapInfoHeader.biWidth + 0x07) >> 3);

if (enteredModule.getRBits() == 1)
fprintf(Grey_2bit_and_Red_1bit_out, "#define WIDTH_RED_BYTES  (%d)\n", (bitmapInfoHeader.biWidth + 0x07) >> 3);


if(enteredModule.getGBits() == 1)
	fprintf(Grey_2bit_and_Red_1bit_out, "#define WIDTH_MONO_BYTES (%d)\n", (bitmapInfoHeader.biWidth + 0x07) >> 3);

	//Now we just loop down the file, line by line (bottom first),
	//create the 16-bit words and spool them out.
	int
		col;
	int
		row;

	//Our pointer into the bitmap data
	unsigned char
		*data_pointer;

	//The width of a line, in bytes, bust be a multiple of 4;
	int
		line_width;

	//3 bytes per pixel, round up to next 4-byte alignment
	line_width = ((3 * bitmapInfoHeader.biWidth) + 3) & ~0x03;

	//---------------------------------------------------------------------------
	if (enteredModule.getGBits() == 2)
	{

#if ONE_DIM
		fprintf(Grey_2bit_and_Red_1bit_out,
			"\nconst uint8_t Grey_2BPP[%d] PROGMEM = \n  {",
			bitmapInfoHeader.biHeight*((bitmapInfoHeader.biWidth + 0x03) >> 2));
#else
		fprintf(Grey_2bit_and_Red_1bit_out,
			"\nconst uint8_t Grey_2BPP[%d][%d] PROGMEM =\n  {{",
			bitmapInfoHeader.biHeight,
			(bitmapInfoHeader.biWidth + 0x03) >> 2);
#endif

		for (row = 0; row < bitmapInfoHeader.biHeight; row++)
		{
			int
				first_data_of_this_line_written;
			first_data_of_this_line_written = 0;

			//Point to the current row in the bitmap data (starting at the bottom)
			data_pointer = bitmapData + (bitmapInfoHeader.biHeight - 1 - row)*line_width;

			//We need to push 4 pixels into one 8-bit byte.
			unsigned char
				this_2bpp_byte;
			int
				sub_pixel_count;

			this_2bpp_byte = 0x00;
			sub_pixel_count = 0;

			//work across the row.
			for (col = 0; col < bitmapInfoHeader.biWidth; col++)
			{
				unsigned char
					red;
				unsigned char
					green;
				unsigned char
					blue;
				//pull the pixel out of the stream
				blue = *data_pointer++;
				green = *data_pointer++;
				red = *data_pointer++;

				//Now decide what color of the ink we are
				//going to use for this pixel.
				unsigned char
					sub_pixel_2bit;

				//Check for the special case of it being a red pixel
				if ((171 < red) && (green < 85) && (blue < 85))
				{
					//since we are writing the black/grey/white plane, we
					//want to put white wherre this red pixel would fall.
					sub_pixel_2bit = 0x00;  // 00 = White
				}
				else
				{
					//See if it is a white pixel
					if ((171 < red) && (171 < green) && (171 < blue))
					{
						sub_pixel_2bit = 0x00;  // 00 = White
					}
					else
					{
						//See if it is a 50% gray pixel
						if ((85 < red) && (red < 171) &&
							(85 < green) && (green < 171) &&
							(85 < blue) && (blue < 171))
						{
							sub_pixel_2bit = 0x01;  // 01 or 10 = Grey 
						}
						else
						{
							//default to black
							sub_pixel_2bit = 0x03;  //11 = black
						}
					}
				}

				//Insert those bits into the correct slot of this_2bpp_byte
				this_2bpp_byte |= (sub_pixel_2bit) << ((3 - sub_pixel_count) * 2);

				//Move to the next sub-pixel
				sub_pixel_count++;
				//If this byte is full, write it out and clear for the 
				//next 4 bytes.
				if (3 < sub_pixel_count)
				{
					if (first_data_of_this_line_written)
					{
						fprintf(Grey_2bit_and_Red_1bit_out, ",");
					}
					first_data_of_this_line_written = 1;
					//Then write out the 8-bit packed pixel
					fprintf(Grey_2bit_and_Red_1bit_out, "0x%02X", this_2bpp_byte);
					//Reset the byte accumulator and count
					this_2bpp_byte = 0;
					sub_pixel_count = 0;
				}
			}
			//This is the last entry for this line. If we have not just written
			//out the last byte, of this line write it out now.
			if (sub_pixel_count)
			{
				if (first_data_of_this_line_written)
				{
					fprintf(Grey_2bit_and_Red_1bit_out, ",");
				}
				first_data_of_this_line_written = 1;
				//Then write out the 8bit packed pixel.
				fprintf(Grey_2bit_and_Red_1bit_out, "0x%02X", this_2bpp_byte);
			}

#if ONE_DIM
			//That is the end of one line. Complete the C syntax.
			if (row == (bitmapInfoHeader.biHeight - 1))
			{
				fprintf(Grey_2bit_and_Red_1bit_out, "};\n");
			}
			else
			{
				fprintf(Grey_2bit_and_Red_1bit_out, ",\n   ");
			}
#else
			//That is the end of one line. Complete the C syntax.
			if (row == (bitmapInfoHeader.biHeight - 1))
			{
				fprintf(Grey_2bit_and_Red_1bit_out, "}};\n");
			}
			else
			{
				fprintf(Grey_2bit_and_Red_1bit_out, "},\n   {");
			}
#endif
		}
	}//  OUTPUT2BPPGREY
	//---------------------------------------------------------------------------
	if (enteredModule.getRBits() == 1 || enteredModule.getYBits() == 1)
	{
		//The 2-bit grey is done, now dump out the 1-bit red
		//Write out the header information to the red file.
#if ONE_DIM
		fprintf(Grey_2bit_and_Red_1bit_out,
			"\nconst uint8_t Red_1BPP[%d] PROGMEM =\n  {",
			bitmapInfoHeader.biHeight*((bitmapInfoHeader.biWidth + 0x07) >> 3));
#else
		fprintf(Grey_2bit_and_Red_1bit_out,
			"\nconst uint8_t Red_1BPP[%d][%d] PROGMEM =\n  {{",
			bitmapInfoHeader.biHeight,
			(bitmapInfoHeader.biWidth + 0x07) >> 3);
#endif
		//Now we just loop down the file, line by line (bottom first),
		for (row = 0; row < bitmapInfoHeader.biHeight; row++)
		{
			int
				first_data_of_this_line_written;
			first_data_of_this_line_written = 0;

			//Point to the current row in the bitmap data (starting at the bottom)
			data_pointer = bitmapData + (bitmapInfoHeader.biHeight - 1 - row)*line_width;

			//We need to push 8 pixels into one 8-bit byte.
			unsigned char
				this_1bpp_byte;
			int
				sub_pixel_count;

			this_1bpp_byte = 0x00;
			sub_pixel_count = 0;

			//work across the row.
			for (col = 0; col < bitmapInfoHeader.biWidth; col++)
			{
				unsigned char
					red;
				unsigned char
					green;
				unsigned char
					blue;
				//pull the pixel out of the stream
				blue = *data_pointer++;
				green = *data_pointer++;
				red = *data_pointer++;

				//Now decide what color of the ink we are
				//going to use for this pixel.
				unsigned char
					sub_pixel_1bit;

				//Check for the special case of it being a red pixel
        if (enteredModule.getRBits() == 1)
        {
          if ((171 < red) && (green < 110) && (blue < 110))
          {
            //since we are writing the black/grey/white plane, we
            //want to put white wherre this red pixel would fall.
            sub_pixel_1bit = 0x01;  // 1 = Red
          }
          else
          {
            //default to no ink
            sub_pixel_1bit = 0x00;  // 10 = White
          }
        }
        //Check for the special case of it being a yellow pixel
        else if (enteredModule.getYBits() == 1)
        {
          if ((228 < red) && (180 < green) && (blue < 30))
          {
            //since we are writing the black/grey/white plane, we
            //want to put white wherre this red pixel would fall.
            sub_pixel_1bit = 0x01;  // 1 = Red
          }
          else
          {
            //default to no ink
            sub_pixel_1bit = 0x00;  // 10 = White
          }
        }


				//Insert those bits into the correct slot of this_2bpp_byte
				this_1bpp_byte |= (sub_pixel_1bit) << (7 - sub_pixel_count);

				//Move to the next sub-pixel
				sub_pixel_count++;
				//If this byte is full, write it out and clear for the 
				//next 4 bytes.
				if (7 < sub_pixel_count)
				{
					if (first_data_of_this_line_written)
					{
						fprintf(Grey_2bit_and_Red_1bit_out, ",");
					}
					first_data_of_this_line_written = 1;

					//Then write out the 8-bit packed pixel byte
					fprintf(Grey_2bit_and_Red_1bit_out, "0x%02X", this_1bpp_byte);
					//Reset the byte accumulator and count
					this_1bpp_byte = 0;
					sub_pixel_count = 0;
				}
			}
			//This is the last entry for this line. If we have not just written
			//out the last byte, of this line write it out now.
			if (sub_pixel_count)
			{
				if (first_data_of_this_line_written)
				{
					fprintf(Grey_2bit_and_Red_1bit_out, ",");
				}
				first_data_of_this_line_written = 1;

				//Then write out the 16-bit packed pixel to the bin file.
				fprintf(Grey_2bit_and_Red_1bit_out, "0x%02X", this_1bpp_byte);
			}
#if ONE_DIM
			//That is the end of one line. Complete the C syntax.
			if (row == (bitmapInfoHeader.biHeight - 1))
			{
				fprintf(Grey_2bit_and_Red_1bit_out, "};\n");
			}
			else
			{
				fprintf(Grey_2bit_and_Red_1bit_out, ",\n   ");
			}
#else
			//That is the end of one line. Complete the C syntax.
			if (row == (bitmapInfoHeader.biHeight - 1))
			{
				fprintf(Grey_2bit_and_Red_1bit_out, "}};\n");
			}
			else
			{
				fprintf(Grey_2bit_and_Red_1bit_out, "},\n   {");
			}
#endif
		}
	}  //  OUTPUT1BPPRED
	//---------------------------------------------------------------------------

	if (enteredModule.getGBits() == 1)
	{
		//Write out the header information to the red file.
#if ONE_DIM
		fprintf(Grey_2bit_and_Red_1bit_out,
			"\nconst uint8_t Mono_1BPP[%d] PROGMEM =\n  {",
			bitmapInfoHeader.biHeight*((bitmapInfoHeader.biWidth + 0x07) >> 3));
#else
		fprintf(Grey_2bit_and_Red_1bit_out,
			"\nconst uint8_t Mono_1BPP[%d][%d] PROGMEM =\n  {{",
			bitmapInfoHeader.biHeight,
			(bitmapInfoHeader.biWidth + 0x07) >> 3);
#endif
		//Now we just loop down the file, line by line (bottom first),
		for (row = 0; row < bitmapInfoHeader.biHeight; row++)
		{
			int
				first_data_of_this_line_written;
			first_data_of_this_line_written = 0;

			//Point to the current row in the bitmap data (starting at the bottom)
			data_pointer = bitmapData + (bitmapInfoHeader.biHeight - 1 - row)*line_width;

			//check to see if the module updates from left to right, if it's right to left we need to move the pointer
			if (!enteredModule.getLTR())
			{
				data_pointer += ((bitmapInfoHeader.biWidth) * 3) - 1;
			}

			//We need to push 8 pixels into one 8-bit byte.
			unsigned char
				this_1bpp_byte;
			int
				sub_pixel_count;

			this_1bpp_byte = 0x00;
			sub_pixel_count = 0;

			//work across the row
			for (col = 0; col < bitmapInfoHeader.biWidth; col++)
			{
				unsigned char
					red;
				unsigned char
					green;
				unsigned char
					blue;

				//pull the pixel out of the stream first statement is if the display goes left to right
				//second statement is if the display goes right to left
				if (enteredModule.getLTR())
				{
					red = *data_pointer++;
					green = *data_pointer++;
					blue = *data_pointer++;
					// printf("\nr: %i\t|g: %i\t|b: %i\t|", red, green, blue);
				}
				else 
				{
					red = *data_pointer--;
					green = *data_pointer--;
					blue = *data_pointer--;
				}

				//Now decide what color of the ink we are
				//going to use for this pixel.
				unsigned char
					sub_pixel_1bit;

				//White is just above 50% grey
				if (127 > ((red*.21)+(green*.72)+(blue*.07)))
				{
					//TODO check this 
					//black, put the ink
					if (!enteredModule.getReverseColor())
					{
						sub_pixel_1bit = 0x01;  // 1 = black
					}
					else
					{
						sub_pixel_1bit = 0x00;  // 0 = black
					}
					
				}
				else
				{
					//This is white, no ink
					if (!enteredModule.getReverseColor())
					{
						sub_pixel_1bit = 0x00;  // 0 = white
					}
					else
					{
						sub_pixel_1bit = 0x01;  // 1 = white
					}

				}

				//Insert those bits into the correct slot of this_2bpp_byte
				this_1bpp_byte |= (sub_pixel_1bit) << (7 - sub_pixel_count);

				//Move to the next sub-pixel
				sub_pixel_count++;
				//If this byte is full, write it out and clear for the 
				//next 4 bytes.
				if (7 < sub_pixel_count)
				{
					if (first_data_of_this_line_written)
					{
						fprintf(Grey_2bit_and_Red_1bit_out, ",");
					}
					first_data_of_this_line_written = 1;

					//Then write out the 8-bit packed pixel byte
					fprintf(Grey_2bit_and_Red_1bit_out, "0x%02X", this_1bpp_byte);
					//Reset the byte accumulator and count
					this_1bpp_byte = 0;
					sub_pixel_count = 0;
				}
			}
			//This is the last entry for this line. If we have not just written
			//out the last byte, of this line write it out now.
			if (sub_pixel_count)
			{
				if (first_data_of_this_line_written)
				{
					fprintf(Grey_2bit_and_Red_1bit_out, ",");
				}
				first_data_of_this_line_written = 1;

				//Then write out the 16-bit packed pixel to the bin file.
				fprintf(Grey_2bit_and_Red_1bit_out, "0x%02X", this_1bpp_byte);
			}
#if ONE_DIM
			//That is the end of one line. Complete the C syntax.
			if (row == (bitmapInfoHeader.biHeight - 1))
			{
				fprintf(Grey_2bit_and_Red_1bit_out, "};\n");
			}
			else
			{
				fprintf(Grey_2bit_and_Red_1bit_out, ",\n   ");
			}
#else
			//That is the end of one line. Complete the C syntax.
			if (row == (bitmapInfoHeader.biHeight - 1))
			{
				fprintf(Grey_2bit_and_Red_1bit_out, "}};\n");
			}
			else
			{
				fprintf(Grey_2bit_and_Red_1bit_out, "},\n   {");
			}
#endif
		}
	}  // OUTPUT1BPPMONO
	//---------------------------------------------------------------------------

	  //Done with the output file.
	fclose(Grey_2bit_and_Red_1bit_out);

	//free the memory allocated by LoadBitmapFile
	free(bitmapData);

	printf("Complete.\n");

	//Indicate success, exit
	 return 0;
}
//===========================================================================
