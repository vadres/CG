#include "color.h"
Color::Color(PIXEL_TYPE R, PIXEL_TYPE G, PIXEL_TYPE B, PIXEL_TYPE A)
{
    this->R = R;
    this->G = G;
    this->B = B;
    this->A = A;
}


float min(float a, float b) {
    if (a <= b) {
        return a;
    } else {
        return b;
    }
}

void Color::fromVector3f(const Vector3f &v) {

    R = (PIXEL_TYPE)( min(1.0f, v.X()) * 255);
    G = (PIXEL_TYPE)( min(1.0f, v.Y()) * 255);
    B = (PIXEL_TYPE)( min(1.0f, v.Z()) * 255);
}

Vector3f Color::toVector3f() {
    return Vector3f(R/255.0f, G/255.0f, B/255.0f);
}

bool Color::operator ==(const Color &c) {
    return R == c.R && G == c.G && B == c.B && A == c.A;
}

Color& Color::operator =(const Color &c) {
    if (this != &c) {
        this->R = c.R;
        this->G = c.G;
        this->B = c.B;
        this->A = c.A;
    }
    return *this;
}
