#include <iostream>
#include <string>
#include <cstdlib>  // For exit() function (cross-platform)
#include <vector>

// This array classifies the existing ePaper modules

class Module {
private:
    std::string moduleMaster;
    int gBits, rBits, yBits;
    int modWidth, modLength;
    bool reverseColor;
    bool leftToRight;

public:
    void setModuleType(std::string enteredModule);
    int getWidth();
    int getLength();
    int getRBits();
    int getYBits();
    int getGBits();
    bool getLTR();
    bool getReverseColor();
};

void Module::setModuleType(std::string enteredModule)
{
    bool found = false;
    moduleMaster = enteredModule;
    
    // Add checks for each module
    if (enteredModule == "CFAP104212C00213") {
        gBits = 1;
        rBits = 1;
        yBits = 0;
        modWidth = 104;
        modLength = 212;
        reverseColor = false;
        leftToRight = true;
    } else if (enteredModule == "CFAP122250A00213") {
        gBits = 1;
        rBits = 0;
        yBits = 0;
        modWidth = 122;
        modLength = 250;
        reverseColor = false;
        leftToRight = true;
    } else if (enteredModule == "CFAP128296A00290") {
        gBits = 1;
        rBits = 0;
        yBits = 0;
        modWidth = 128;
        modLength = 296;
        reverseColor = false;
        leftToRight = true;
    } else if (enteredModule == "CFAP128296C00290") {
        gBits = 1;
        rBits = 0;
        yBits = 0;
        modWidth = 128;
        modLength = 296;
        reverseColor = false;
        leftToRight = true;
    } else if (enteredModule == "CFAP128296D00290") {
        gBits = 1;
        rBits = 1;
        yBits = 0;
        modWidth = 128;
        modLength = 296;
        reverseColor = false;
        leftToRight = true;
    } else if (enteredModule == "CFAP128296E00290") {
        gBits = 1;
        rBits = 0;
        yBits = 1;
        modWidth = 128;
        modLength = 296;
        reverseColor = false;
        leftToRight = true;
    } else if (enteredModule == "CFAP152152A00154") {
        gBits = 1;
        rBits = 1;
        yBits = 0;
        modWidth = 152;
        modLength = 152;
        reverseColor = false;
        leftToRight = true;
    } else if (enteredModule == "CFAP176264A00270") {
        gBits = 1;
        rBits = 1;
        yBits = 0;
        modWidth = 176;
        modLength = 264;
        reverseColor = false;
        leftToRight = true;
    } else if (enteredModule == "CFAP176264B00270") {
        gBits = 1;
        rBits = 0;
        yBits = 0;
        modWidth = 176;
        modLength = 264;
        reverseColor = false;
        leftToRight = true;
    } else if (enteredModule == "CFAP200200A00154") {
        gBits = 1;
        rBits = 0;
        yBits = 0;
        modWidth = 200;
        modLength = 200;
        reverseColor = false;
        leftToRight = false;
    } else if (enteredModule == "CFAP400300A00420") {
        gBits = 1;
        rBits = 1;
        yBits = 0;
        modWidth = 400;
        modLength = 300;
        reverseColor = false;
        leftToRight = true;
    } else if (enteredModule == "CFAP400300B00420") {
        gBits = 1;
        rBits = 0;
        yBits = 0;
        modWidth = 400;
        modLength = 300;
        reverseColor = false;
        leftToRight = true;
    } else if (enteredModule == "CFAP400300C00420") {
        gBits = 1;
        rBits = 0;
        yBits = 1;
        modWidth = 400;
        modLength = 300;
        reverseColor = false;
        leftToRight = true;
    } else if (enteredModule == "CFAP600448A00750") {
        gBits = 1;
        rBits = 0;
        yBits = 0;
        modWidth = 600;
        modLength = 448;
        reverseColor = false;
        leftToRight = true;
    } else if (enteredModule == "CFAP640384A00750") {
        gBits = 1;
        rBits = 0;
        yBits = 0;
        modWidth = 640;
        modLength = 384;
        reverseColor = false;
        leftToRight = true;
    } else if (enteredModule == "Custom300x400") {
        gBits = 1;  // Assuming 1 bit for grayscale (black and white)
        rBits = 0;  // No red
        yBits = 0;  // No yellow
        modWidth = 300;   // Width of the display (300 pixels)
        modLength = 400;  // Height of the display (400 pixels)
        reverseColor = false;  // Default polarity (not inverted)
        leftToRight = true;    // Update from left to right
    } else if (enteredModule == "Custom300x400in") {
        gBits = 1;  // Assuming 1 bit for grayscale (black and white)
        rBits = 0;  // No red
        yBits = 0;  // No yellow
        modWidth = 300;   // Width of the display (300 pixels)
        modLength = 400;  // Height of the display (400 pixels)
        reverseColor = true;  // Default polarity (inverted)
        leftToRight = true;    // Update from left to right
    } else if (enteredModule == "Custom300x395") {
        gBits = 1;  // Assuming 1 bit for grayscale (black and white)
        rBits = 0;  // No red
        yBits = 0;  // No yellow
        modWidth = 300;   // Width of the display (300 pixels)
        modLength = 395;  // Height of the display (395 pixels)
        reverseColor = false;  // Default polarity (not inverted)
        leftToRight = true;    // Update from left to right
    } else if (enteredModule == "Custom300x380") {
        gBits = 1;  // Assuming 1 bit for grayscale (black and white)
        rBits = 0;  // No red
        yBits = 0;  // No yellow
        modWidth = 300;   // Width of the display (300 pixels)
        modLength = 380;  // Height of the display (380 pixels)
        reverseColor = false;  // Default polarity (not inverted)
        leftToRight = true;    // Update from left to right
    } else {
        // Print a message for invalid module and available modules
        std::cout << "Module part number " << enteredModule << " is not a valid part number.\n";
        std::cout << "The following are valid part numbers:\n";
        std::vector<std::string> moduleType = {
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
        
        for (const auto& module : moduleType) {
            std::cout << module << std::endl;
        }
        exit(3);
    }
}

int Module::getWidth() {
    if (modWidth != 0) {
        return modWidth;
    } else {
        std::cerr << "No horizontal pixel value stored." << std::endl;
        return 0;
    }
}

int Module::getLength() {
    if (modLength != 0) {
        return modLength;
    } else {
        std::cerr << "No vertical pixel value stored." << std::endl;
        return 0;
    }
}

int Module::getRBits() {
    if (rBits != 0) {
        return rBits;
    } else {
        std::cerr << "No red bit value stored for this display." << std::endl;
        return 0;
    }
}

int Module::getYBits() {
    if (yBits != 0) {
        return yBits;
    } else {
        std::cerr << "No yellow bit value stored for this display." << std::endl;
        return 0;
    }
}

int Module::getGBits() {
    if (gBits != 0) {
        return gBits;
    } else {
        std::cerr << "No gray bit value stored for this display." << std::endl;
        return 0;
    }
}

bool Module::getLTR() {
    return leftToRight;
}

bool Module::getReverseColor() {
    return reverseColor;
}
