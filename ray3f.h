#ifndef RAY3F_H
#define RAY3F_H

#include "vector3f.h"

/**
 * @brief The Ray3f class
 */
class Ray3f
{
    Vector3f origin;
    Vector3f direction;
public:
    /**
     * @brief Ray3f
     * @param origin
     * @param direction
     */
    Ray3f(const Vector3f &origin=Vector3f(0,0,0), const Vector3f &direction=Vector3f(0,0,0));
    Ray3f(const Ray3f &ray);
    Vector3f getOrigin() const;
    Vector3f getDirection() const;
    void setDirection(const Vector3f &dir);
    void setOrigin(const Vector3f &orig);
    bool operator ==(const Ray3f &r) const;
    Ray3f& operator=(const Ray3f &r);

    Vector3f pointAt(float t) const;
};

#endif // RAY3F_H
