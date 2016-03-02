#include "triangle.h"

#include <cstdio>
Triangle::Triangle(const Vector3f &A,
                   const Vector3f &B,
                   const Vector3f &C)
{
    this->a = A;
    this->b = B;
    this->c = C;
    this->material = new Material();
    this->normal = ((b-a)*(c-a)).normalize();

}

float t_flag = -1;
RayCastingResult* Triangle::hit(const Ray3f &ray, RayCastingResult *result) {
    t_flag = -1;
    if (!result) {
        result = new RayCastingResult();
    }

    result->object = this;

    Vector3f p;
    float epslon = 1.0e-10;
    if ( test_with_plane(ray, p) )  {
        if (in(p)) {
            if (t_flag > epslon) {
                result->addResult(p, t_flag);
                result->material = getMaterial();
                result->normal = getNormal();
                //printf("%f, %f, %f\n", result->normal.X(), result->normal.Y(), result->normal.Z());
            }
            t_flag = -1;
        }
    }

    return result;
}

bool Triangle::in(const Vector3f &q){
    //const float error = 1.0e-10f;
    float dabc = ((b-a) * (c-a)).lenght();
    float dqbc = ((b-q) * (c-q)).lenght();
    float daqc = ((q-a) * (c-a)).lenght();
    float dabq = ((b-a) * (q-a)).lenght();

    float u = dqbc/dabc;
    float v = daqc/dabc;
    float w = dabq/dabc;
//    printf("(%f, %f, %f)\n", u, v, w);
    return u >= 0 && u <= 1.0f &&
           v >= 0 && v <= 1.0f &&
           w >= 0 && w <= 1.0f;
}


Vector3f Triangle::getNormal(const Vector3f &point) {
    return this->normal;
}

Vector3f Triangle::getNormal() {
    return this->normal;
}


bool Triangle::test_with_plane(const Ray3f &ray, Vector3f &out) {
    Vector3f D = ray.getDirection();
    Vector3f O = ray.getOrigin();
    Vector3f P = this->a;
    Vector3f N = normal;

    float d = D.dot(N);
    if (d != 0) {
        float t = (P.dot(N) - O.dot(N))/d;
        t_flag = t;
        out = ray.pointAt(t);
        return true;
    } else {
        return false;
    }
}


float Triangle::getArea(){
    return ((b-a) * (c-a)).lenght()/2.0f;
}


Material* Triangle::getMaterial() {
    return this->material;
}

string Triangle::getName() {
    return "triangle";
}


Triangle::~Triangle(){
    if (material) {
        delete material;
    }
}
