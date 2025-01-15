#ifndef __MODULETYPE_H__
#define __MODULETYPE_H__

#include <string>

class Module
{
private:
    std::string moduleMaster;
    int rBits;
    int yBits;
    int gBits;
    int modWidth;
    int modLength;
    bool reverseColor;
    bool leftToRight;

public:
    void setModuleType(std::string);
    int getWidth(void);
    int getLength(void);
    int getRBits(void);
    int getYBits(void);
    int getGBits(void);
    bool getLTR(void);
    bool getReverseColor(void);
};

#endif
