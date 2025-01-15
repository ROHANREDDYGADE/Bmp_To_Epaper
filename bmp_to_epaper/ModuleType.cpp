//============================================================================
// 
//
// 
// 
//============================================================================
#include "stdafx.h"
#include "ModuleType.h"
//This array classifies the existing ePaper modules


//============================================================================
//Information on the following block of code:
//gBits sets the number of bits the ePaper uses for black and white
//rBits sets the number of bits the ePaper uses for red
//yBits sets the number of bits the ePaper uses for yellow
//
//modWidth sets the width of the dispaly
//modLength sets the length of the display
//reverseColor sets which polarity the bits are stored in the bitmap 
//  - this can be changed if inverted colors are desired.
//
//leftToRight true if the screen is set to update left to right, false if vice versa 
//  - this can be changed if one wants to mirror the image. Most displays also have
//    a setting that can be changed for the same effect

void Module::setModuleType(std::string enteredModule)
{
	bool found = false;
    moduleMaster = enteredModule;
    if (enteredModule == "CFAP104212C00213")
    {
      gBits = 1;
      rBits = 1;
      yBits = 0;

      modWidth = 104;
      modLength = 212;
      reverseColor = false;
      leftToRight = true;
    }
  else if (enteredModule == "CFAP122250A00213")
  {
    gBits = 1;
    rBits = 0;
    yBits = 0;

    modWidth = 122;
    modLength = 250;
    reverseColor = false;
    leftToRight = true;
  }
    else if (enteredModule == "CFAP128296A00290")
    {
      gBits = 1;
      rBits = 0;
      yBits = 0;

      modWidth = 128;
      modLength = 296;
      reverseColor = false;
      leftToRight = true;
    }
  else if (enteredModule == "CFAP128296C00290")
  {
    gBits = 1;
    rBits = 0;
    yBits = 0;

    modWidth = 128;
    modLength = 296;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP128296D00290")
  {
    gBits = 1;
    rBits = 1;
    yBits = 0;

    modWidth = 128;
    modLength = 296;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP128296E00290")
  {
    gBits = 1;
    rBits = 0;
    yBits = 1;

    modWidth = 128;
    modLength = 296;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP152152A00154")
  {
    gBits = 1;
    rBits = 1;
    yBits = 0;

    modWidth = 152;
    modLength = 152;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP176264A00270")
  {
    gBits = 1;
    rBits = 1;
    yBits = 0;

    modWidth = 176;
    modLength = 264;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP176264B00270")
  {
    gBits = 1;
    rBits = 0;
    yBits = 0;

    modWidth = 176;
    modLength = 264;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP200200A00154")
  {
    gBits = 1;
    rBits = 0;
    yBits = 0;

    modWidth = 200;
    modLength = 200;
    reverseColor = false;
    leftToRight = false;
  }
  else if (enteredModule == "CFAP400300A00420")
  {
    gBits = 1;
    rBits = 1;
    yBits = 0;

    modWidth = 400;
    modLength = 300;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP400300B00420")
  {
    gBits = 1;
    rBits = 0;
    yBits = 0;

    modWidth = 400;
    modLength = 300;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP400300C00420")
  {
    gBits = 1;
    rBits = 0;
    yBits = 1;

    modWidth = 400;
    modLength = 300;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP600448A00750")
  {
    gBits = 1;
    rBits = 0;
    yBits = 0;

    modWidth = 600;
    modLength = 448;
    reverseColor = false;
    leftToRight = true;
  }
  else if (enteredModule == "CFAP640384A00750")
  {
    gBits = 1;
    rBits = 0;
    yBits = 0;

    modWidth = 640;
    modLength = 384;
    reverseColor = false;
    leftToRight = true;
  }
      // Add the 300x400 ePaper module
    else if (enteredModule == "Custom300x400")
    {
        gBits = 1;  // Assuming 1 bit for grayscale (black and white)
        rBits = 0;  // No red
        yBits = 0;  // No yellow

        modWidth = 300;   // Width of the display (300 pixels)
        modLength = 400;  // Height of the display (400 pixels)
        reverseColor = false;  // Default polarity (not inverted)
        leftToRight = true;    // Update from left to right
    }
        else if (enteredModule == "Custom300x400in")
    {
        gBits = 1;  // Assuming 1 bit for grayscale (black and white)
        rBits = 0;  // No red
        yBits = 0;  // No yellow

        modWidth = 300;   // Width of the display (300 pixels)
        modLength = 400;  // Height of the display (400 pixels)
        reverseColor = true;  // Default polarity (not inverted)
        leftToRight = true;    // Update from left to right
    }
    else if (enteredModule == "Custom300x395")
    {
        gBits = 1;  // Assuming 1 bit for grayscale (black and white)
        rBits = 0;  // No red
        yBits = 0;  // No yellow

        modWidth = 300;   // Width of the display (300 pixels)
        modLength = 395;  // Height of the display (400 pixels)
        reverseColor = false;  // Default polarity (not inverted)
        leftToRight = true;    // Update from left to right
    }
        else if (enteredModule == "Custom300x380")
    {
        gBits = 1;  // Assuming 1 bit for grayscale (black and white)
        rBits = 0;  // No red
        yBits = 0;  // No yellow

        modWidth = 300;   // Width of the display (300 pixels)
        modLength = 380;  // Height of the display (400 pixels)
        reverseColor = false;  // Default polarity (not inverted)
        leftToRight = true;    // Update from left to right
    }
  else
	{
    int size = 12;
    std::string moduleType[] =
    {
      "CFAP104212C00213",
      "CFAP122250A00213",
      "CFAP128296A00290",
      "CFAP128296C00290",
      "CFAP128296D00290",
      "CFAP128296E00290",
      "CFAP152152A00154",
      "CFAP176264A00270",
      "CFAP176264B00270",
      "CFAP200200A00154",
      "CFAP400300C00420",
      "CFAP640384A00750",
      "Custom300x400",
      "Custom300x400in",
      "Custom300x395",
      "Custom300x380"
    };
		printf("Module part number %s is not a valid Part number.\n", enteredModule.c_str());
		printf("The following are valid partnumbers:\n");
		for (int i = 0; i < size; i++)
		{
			printf("%s\n", moduleType[i].c_str());
		}
		system("pause");
		exit(3);
	}
}

int Module::getWidth()
{
	if (modWidth != 0)
	{
		return(modWidth);
	}
	else
	{
		printf("No horizontal pixel value stored.");
		return 0;
	}
}


int Module::getLength()
{
	if (modLength != 0)
	{
		return(modLength);
	}
	else
	{
		printf("No vertical pixel value stored.");
		return 0;
	}
}

int Module::getRBits(void)
{
  if (rBits != 0)
  {
    return rBits;
  }
  else {
    printf("no red bit value stored for this display");
    return 0;
  }
}

int Module::getYBits(void)
{
  if (yBits != 0)
  {
    return yBits;
  }
  else {
    printf("no yellow bit value stored for this display");
    return 0;
  }
}

int Module::getGBits()
{
	if (gBits != 0)
	{
		return gBits;
	}
	else { 
  printf("no grey bit value stored for this display");
	return 0;
	}
}

bool Module::getLTR(void)
{
	return leftToRight;

}
bool Module::getReverseColor(void)
{
	return reverseColor;
}