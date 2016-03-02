#include "vector3f.h"

Vector3f::Vector3f(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3f::Vector3f(const Vector3f &copy) {
    this->x = copy.x;
    this->y = copy.y;
    this->z = copy.z;
}

Vector3f Vector3f::mult(float scale) const {
    return Vector3f(this->x * scale, this->y * scale, this->z * scale);
}

Vector3f Vector3f::mult(const Vector3f v) const {
    return Vector3f(this->x * v.x, this->y * v.y, this->z * v.z);
}

float Vector3f::dot(const Vector3f &v) const {
    return x * v.x + y * v.y + z * v.z;
}

Vector3f Vector3f::operator  +(const Vector3f &v) const {
    return Vector3f(x + v.x, y + v.y, z + v.z);
}

Vector3f Vector3f::operator  -(const Vector3f &v) const {
    return Vector3f(x - v.x, y - v.y, z - v.z);
}

Vector3f Vector3f::operator *(const Vector3f &v) const {
    return Vector3f(y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - y * v.x);
}

bool Vector3f::operator ==(const Vector3f &v) const {
    return (x == v.x && y == v.y && z == v.z);
}

Vector3f& Vector3f::operator=(const Vector3f &v) {
    if ( &v != this) {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
    }
    return *this;
}

float Vector3f::operator [](char c) const {
    switch(c) {
        case 'x':
            return x;
        case 'y':
            return y;
        case 'z':
            return z;
        default:
            return x;
    }
}


float Vector3f::lenght() const {
    return sqrt(x*x + y*y + z*z);
}

float Vector3f::lenght2() const {
    return dot(*this);
}

Vector3f Vector3f::project(const Vector3f &v) const{
    return (v * (this->dot(v)/v.lenght2()));
}

Vector3f Vector3f::normalize() const {
    float size = this->lenght();
    Vector3f r(*this);
    if (size != 0) {
        r.x = x/size;
        r.y = y/size;
        r.z = z/size;
    }
    return r;
}

float Vector3f::X() const {
    return x;
}

float Vector3f::Y() const {
    return y;
}

float Vector3f::Z() const {
    return z;
}
