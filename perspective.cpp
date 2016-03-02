#include "perspective.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.1415926535897
#endif

Perspective::Perspective(float fov, float asp, float n)
{
    this->fieldOfView = fov; //Angulo de abertura da camera ou field of view.
    this->aspectRatio = asp; //razao entre largura e altura
    this->near = n; //distancia do plano mais proximo da camera
}

Vector3f Perspective::map(const Vector3f &p) {

    float d = (p.Z()/near + 1);
    float x = p.X()/d;
    float y = p.Y()/d;
    return Vector3f(x, y, 0);
}

void Perspective::set(float fov, float ar, float n) {
    this->fieldOfView = fov;
    this->aspectRatio = ar;
    this->near = n;
}

float Perspective::delta_x(float wres) {
    return get_viewportwidth()/wres;
}

float Perspective::delta_y(float hres) {
    return get_viewportheight()/hres;
}

float Perspective::get_near() {
    return near;
}

float Perspective::get_viewportwidth() {
    return get_viewportheight()*aspectRatio;
}

float Perspective::get_viewportheight() {
    return 2 * near * tan( (fieldOfView * M_PI)/360.0f );
}

float Perspective::get_fieldofview() {
    return fieldOfView;
}
