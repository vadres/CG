#include "material.h"

Material::Material(Color d, Color sp, Color a, float s)
{
    this->kd = d;
    this->ks = sp;
    this->ka = a;
    this->shineness = s;
    this->reflectionRate = 0.05f;
}

