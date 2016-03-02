#include "light.h"

PointLight::PointLight(const Vector3f &p) {
    this->position = p;
}


Light::Light(string name, LightType *t, const Color &i)
{
    this->intensity = i;
    this->type = t;
    this->name = name;
}

LightType* Light::getType() {
    return this->type;
}

string Light::getName() {
    return this->name;
}

Color Light::getColor() {
    return this->intensity;
}
