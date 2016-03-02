#ifndef SPHERE_H
#define SPHERE_H

#include "object3d.h"
#include "vector3f.h"
#include "raycastingresult.h"
#include "ray3f.h"
#include <cmath>
#include "material.h"
#include "color.h"

/**
 * @brief The Sphere class
 */
class Sphere: public Object3D
{
    Vector3f position;
    float radio;
    Material *material;
public:
    Sphere();
    Sphere(const Vector3f &pos, float ra);
    virtual RayCastingResult* hit(const Ray3f &ray, RayCastingResult *result=0);
    virtual Vector3f getNormal(const Vector3f &point);
    virtual Vector3f getNormal();
    virtual Material* getMaterial();
    virtual string getName();
    ~Sphere();
};

#endif // SPHERE_H
