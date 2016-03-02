#include "sphere.h"

Sphere::Sphere() {
    this->position = Vector3f(0,0,0);
    this->radio = 1.0f;
    this->material = new Material();
}

Sphere::Sphere(const Vector3f &pos, float ra) : position(pos), radio(ra)
{
    this->position = pos;
    this->radio = ra;
    this->material = new Material();
}

string Sphere::getName() {
    return "sphere";
}

RayCastingResult* Sphere::hit(const Ray3f &ray, RayCastingResult *result) {
    if (!result) {
        result = new RayCastingResult();
    }

    result->object = this;

    float ddotd = ray.getDirection().dot(ray.getDirection());
    Vector3f emc = ray.getOrigin() - position;
    float emcdotemc = emc.dot(emc);
    float ddotemc = ray.getDirection().dot(emc);
    float ddotemc2 = ddotemc * ddotemc;

    float delta = ddotemc2 - ddotd * (emcdotemc- radio * radio);
    float sdelta;


    float epslon = 0.0f;

    if (delta == 0) {
        sdelta = sqrt(delta);
        float t1 = (- (ddotemc))/ddotd;
        Vector3f p1 = ray.pointAt(t1);
        if (t1 > epslon) {
            result->addResult(p1, t1);
            result->material = getMaterial();
            result->normal = getNormal(p1);
        }
    } else if (delta > epslon) {
        sdelta = sqrt(delta);
        float t1 = (- ddotemc + sdelta)/ddotd;
        float t2 = (- ddotemc - sdelta)/ddotd;
        Vector3f p1 = ray.pointAt(t1);
        Vector3f p2 = ray.pointAt(t2);
        if (t1 < t2) {
            bool passInt1 = false;
            if (t1 > epslon) {
                passInt1 = true;
                result->addResult(p1, t1);
                result->material = getMaterial();
                result->normal = getNormal(p1);
            }
            if (t2 > epslon) {
                result->addResult(p2, t2);
                if (!passInt1) {
                    result->material = getMaterial();
                    result->normal = getNormal(p2);
                }
            }
        } else {
            bool passInt2 = false;
            if (t2 > epslon) {
                passInt2 = true;
                result->addResult(p2, t2);
                result->material = getMaterial();
                result->normal = getNormal(p2);

            }

            if (t1 > epslon) {
                result->addResult(p1, t1);

                if (!passInt2) {
                    result->material = getMaterial();
                    result->normal = getNormal(p1);
                }
            }
        }
    }

    return result;
}

Vector3f Sphere::getNormal(const Vector3f &point) {
    return (point-position).mult(2).normalize();
}


Vector3f Sphere::getNormal() {
    return Vector3f(0,0,0);
}

Material* Sphere::getMaterial() {
    return this->material;
}


Sphere::~Sphere(){
    if (material) {
        delete material;
    }
}
