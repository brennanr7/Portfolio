#include "RGB.h"

RGB::RGB()
    :r(0), g(0), b(0)
{

}
RGB::RGB(unsigned char red, unsigned char green, unsigned char blue)
    :r(red), g(green), b(blue)
{

}
RGB::RGB(const RGB &other)
    :r(other.r), g(other.g), b(other.b)
{

}

RGB &RGB::operator=(const RGB &other)
{
    r = other.r;
    g = other.g;
    b = other.b;
    return *this;
}

bool RGB::operator==(const RGB &other) const
{
    return (r == other.r && g == other.g && b == other.b);
}
bool RGB::operator!=(const RGB &other) const
{
     return (r != other.r || g != other.g || b != other.b);
}
