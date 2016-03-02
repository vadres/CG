#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector3f.h"
#include "object3d.h"
#include "material.h"

/**
 * @brief The Triangle class
 */
class Triangle: public Object3D
{
    Vector3f a, b, c, normal;
    Material *material;
public:
    Triangle(const Vector3f &A = Vector3f(0.0001f, 0.001f, 0.0001f),
             const Vector3f &B = Vector3f(1.0001f, 0.001f, 0.0001f),
             const Vector3f &C = Vector3f(0.0001f, 1.001f, 0.0001f));

    virtual RayCastingResult* hit(const Ray3f &ray, RayCastingResult *result=0);
    virtual Vector3f getNormal(const Vector3f &point);
    virtual Vector3f getNormal();
    bool in(const Vector3f &p);
    bool test_with_plane(const Ray3f &ray, Vector3f &out);
    float getArea();
    virtual Material* getMaterial();
    virtual string getName();
    ~Triangle();
};

#endif // TRIANGLE_H
