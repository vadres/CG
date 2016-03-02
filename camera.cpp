#include "camera.h"

Camera::Camera(Vector3f p, Vector3f u,
       Vector3f dir, Projection *proj) {

    this->position = p;
    this->up = u.normalize();
    this->direction = dir.normalize();
    this->projection = proj;

}

Vector3f Camera::toCamera(const Vector3f &p) {
    Vector3f w = direction;
    Vector3f u = (up * w).normalize();
    Vector3f v = (w * u).normalize();

    Vector3f tmp = p - position;

    float x = tmp.dot(u);
    float y = tmp.dot(v);
    float z = tmp.dot(w);

    return Vector3f(x,y,z);
}


Vector3f Camera::toWorld(const Vector3f &p) {

    Vector3f w = direction;
    Vector3f u = (up * w).normalize();
    Vector3f v = (u * w).normalize();


    Vector3f ul(u.X(), v.X(), w.X());
    Vector3f vl(u.Y(), v.Y(), w.Y());
    Vector3f wl(u.Z(), v.Z(), w.Z());

    float x =  p.dot(ul) + position.X();
    float y =  p.dot(vl) + position.Y();
    float z =  p.dot(wl) + position.Z();

    return Vector3f(x,y,z);
}

Vector3f Camera::project(const Vector3f &p) {
    return projection->map(p);
}

Vector3f Camera::getPosition() {
    return this->position;
}

Vector3f Camera::getUp() {
    return this->up;
}

Vector3f Camera::getDirection() {
    return this->direction;
}

Projection* Camera::getProjection() {
    return this->projection;
}

void Camera::setDirection(const Vector3f &dir) {
    this->direction = dir.normalize();
}



void Camera::setPosition(const Vector3f &pos) {
    this->position = pos;
}


void Camera::setUp(const Vector3f &up) {
    this->up = up.normalize();
}

Camera::~Camera(){
    if (projection) {
        delete projection;
        projection = 0;
    }
}
