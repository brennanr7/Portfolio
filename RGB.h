#ifndef RGB_H
#define RGB_H

//Simple data structure for RGB colors with range from 0 to 255
struct RGB
{
    unsigned char r;
    unsigned char g;
    unsigned char b;

    RGB();
    RGB(unsigned char red, unsigned char green, unsigned char blue);
    RGB(const RGB &other);

    RGB& operator=(const RGB &other);
    bool operator==(const RGB &other) const;
    bool operator!=(const RGB &other) const;
};

#endif // RGB_H
