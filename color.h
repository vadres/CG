#ifndef COLOR_H
#define COLOR_H

#include "vector3f.h"
#include <cmath>

#define PIXEL_TYPE unsigned char

using namespace std;

/**
 * @brief The Color class
 */
class Color
{
public:
    PIXEL_TYPE R;
    PIXEL_TYPE G;
    PIXEL_TYPE B;
    PIXEL_TYPE A;

    Color(PIXEL_TYPE R=0, PIXEL_TYPE G=0, PIXEL_TYPE B=0, PIXEL_TYPE A=255);

    void fromVector3f(const Vector3f &v);
    Vector3f toVector3f();

    bool operator ==(const Color &c);
    Color& operator =(const Color &c);
};

#endif // COLOR_H
