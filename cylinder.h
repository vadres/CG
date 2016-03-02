#ifndef CYLINDER_H
#define CYLINDER_H

#include "object3d.h"
#include "vector3f.h"
#include "raycastingresult.h"
#include "ray3f.h"
#include <cmath>
#include "material.h"
#include "color.h"

class Cylinder: public Object3D
{
    Vector3f center;
    Vector3f center2;
    Vector3f up;
    Material *material;
    float height;
    float radius;

public:
    Cylinder();
    Cylinder(const Vector3f &pos, const Vector3f &ori, float ra, float h);
    virtual RayCastingResult* hit(const Ray3f &ray, RayCastingResult *result=0);
    virtual Vector3f getNormal(const Vector3f &point);
    virtual Vector3f getNormal();
    virtual Material* getMaterial();
    virtual string getName();
    bool test_plan(const Ray3f &ray, const Vector3f &point, double &t_flag);
    ~Cylinder();
};

#endif // CYLINDER_H
