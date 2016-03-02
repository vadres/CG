#include "ray3f.h"

Ray3f::Ray3f(const Vector3f &origin, const Vector3f &direction) {
    this->origin = origin;
    this->direction = direction;
}

Ray3f::Ray3f(const Ray3f &ray) {
    this->origin = ray.origin;
    this->direction = ray.direction.normalize();
}


Vector3f Ray3f::getOrigin() const {
    return this->origin;
}

Vector3f Ray3f::getDirection() const {
    return this->direction;
}

void Ray3f::setDirection(const Vector3f &dir) {
    this->direction = dir.normalize();
}

void Ray3f::setOrigin(const Vector3f &orig) {
    this->origin = orig;
}

bool Ray3f::operator ==(const Ray3f &r) const {
    return  (this->origin == r.origin && this->direction == r.direction);
}

Ray3f& Ray3f::operator=(const Ray3f &r) {
    if (this != &r) {
        this->origin = r.origin;
        this->direction = r.direction;
    }
    return *this;
}

Vector3f Ray3f::pointAt(float t) const {
    float x = origin.X() + t * direction.X();
    float y = origin.Y() + t * direction.Y();
    float z = origin.Z() + t * direction.Z();
    return Vector3f(x, y, z);
}


