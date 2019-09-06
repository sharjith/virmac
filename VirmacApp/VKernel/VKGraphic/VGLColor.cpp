#include "VGLColor.h"
#include "MMath.h"

VGLColor::VGLColor()
{
    itsRed = 0.5f;
    itsGreen = 0.5f;
    itsBlue = 0.5f;
}

VGLColor::VGLColor(const float& red, const float& green, const float& blue)
{
    itsRed =	(red < 0) ? 0 : ((red > 1) ? 1 : red);
    itsGreen =	(green < 0) ? 0 : ((green > 1) ? 1 : green);
    itsBlue =	(blue < 0) ? 0 : ((blue > 1) ? 1 : blue);
}

VGLColor::~VGLColor()
{
}

void VGLColor::SetValues(const float& red, const float& green, const float& blue)
{
    itsRed =	(red < 0) ? 0 : ((red > 1) ? 1 : red);
    itsGreen =	(green < 0) ? 0 : ((green > 1) ? 1 : green);
    itsBlue =	(blue < 0) ? 0 : ((blue > 1) ? 1 : blue);
}

void VGLColor::SetRed(const float& value)
{
    itsRed =	(value < 0) ? 0 : ((value > 1) ? 1 : value);
}

void VGLColor::SetGreen(const float& value)
{
    itsGreen =	(value < 0) ? 0 : ((value > 1) ? 1 : value);
}


void VGLColor::SetBlue(const float& value)
{
    itsBlue =	(value < 0) ? 0 : ((value > 1) ? 1 : value);
}


float VGLColor::GetRed()   const
{
    return itsRed;
}

float VGLColor::GetGreen() const
{
    return itsGreen;
}

float VGLColor::GetBlue()  const
{
    return itsBlue;
}

