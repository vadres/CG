#include <QImage>
#include <iostream>
#include "vector3f.h"
#include "ray3f.h"
#include "raycastingresult.h"
#include "object3d.h"
#include "sphere.h"
#include "triangle.h"
#include "camera.h"
#include "perspective.h"
#include "projection.h"
#include "material.h"
#include "raytracer.h"
#include "light.h"

bool spherehit_test() {
    cout<<"--------------------------SPHEREHIT_TEST BEGIN-----------------------------------------"<<endl;
    Sphere *sphere = new Sphere();
    Ray3f ray(Vector3f(-10,0,0), Vector3f(1,0,0));

    RayCastingResult *result = sphere->hit(ray);

    if (result->size() != 2) {
        cout<<"RESULT: false"<<endl;
        return false;
    }

    Vector3f pt[] = {Vector3f(-1,0,0), Vector3f(1,0,0)};
    for (unsigned i = 0; i < result->size(); i++) {
        Vector3f p = result->getPoint(i);
        float t = result->getRayPosition(i);

        if (! (p == pt[i]) ) {
            cout<<"RESULT: false"<<endl;
            return false;
        }
        /*
        cout<<"------------------"<<endl;
        cout<<"Result: "<<i<<endl;
        cout<<"Point("<<p.X()<<", "<<p.Y()<<", "<<p.Z()<<")"<<endl;
        cout<<"Position: "<<t<<endl;*/
    }


    delete sphere;
    delete result;
    cout<<"RESULT: true"<<endl;
    cout<<"--------------------------SPHEREHIT_TEST END-----------------------------------------"<<endl;
    return true;
}


bool crossproduct_test() {
    cout<<"--------------------------CROSSPRODUCT_TEST BEGIN-----------------------------------------"<<endl;
    Vector3f i(1, 0, 0);
    Vector3f j(0, 1, 0);
    Vector3f k(0, 0, 1);


    Vector3f r1 = i * j;
    Vector3f r2 = j * k;
    //cout<<r2.X()<<", "<<r2.Y()<<", "<<r2.Z()<<endl;
    bool r = (r1 == k && r2 == i);
    cout<<"RESULT: "<<r<<endl;

    cout<<"--------------------------CROSSPRODUCT_TEST END-----------------------------------------"<<endl;
    return r;
}


bool trianglenormal_test() {
    cout<<"--------------------------TRIANGLENORMAL_TEST BEGIN-----------------------------------------"<<endl;
    Triangle *t1  = new Triangle();

    bool r = t1->getNormal() == Vector3f(0,0,1);

    delete t1;

    cout<<"RESULT: "<<r<<endl;

    cout<<"--------------------------TRIANGLENORMAL_TEST END-----------------------------------------"<<endl;
    return r;
}


bool triangletestwithplan1_test() {
    cout<<"--------------------------TRIANGLEHITTESTWITHPLAN_TEST BEGIN-----------------------------------------"<<endl;
    Triangle *t1  = new Triangle();

    Ray3f ray(Vector3f(0,0,10), Vector3f(1,0,0));

    Vector3f r;
    bool test = t1->test_with_plane(ray, r);

    delete t1;

    cout<<"RESULT: "<<(!test)<<endl;
    cout<<"--------------------------TRIANGLEHITTESTWITHPLAN_TEST END-----------------------------------------"<<endl;
    return !test;
}


bool trianglein_test() {
    cout<<"--------------------------TRIANGLEIN_TEST BEGIN-----------------------------------------"<<endl;

    Triangle *t1 = new Triangle();

    bool r1 = t1->in(Vector3f(0.2f, 0.2f, 0.0f));
    bool r2 = t1->in(Vector3f(1.0f, 1.05f, 0.0f));
    bool r3 = t1->in(Vector3f(0.9f, 1.2f, 0.0f));

    delete t1;
    cout<<"RESULT: "<<(r1 && !r2 && !r3)<<endl;
    cout<<"--------------------------TRIANGLEIN_TEST END-----------------------------------------"<<endl;
    return r1 && !r2 && !r3;
}

bool trianglehit_test() {
    cout<<"--------------------------TRIANGLEHIT_TEST BEGIN-----------------------------------------"<<endl;

    Triangle *t1 = new Triangle();

    Ray3f ray(Vector3f(0.5f, 0.5f, 10), Vector3f(0,0,-1));

    RayCastingResult *result = t1->hit(ray);

    bool r1 = (result->size() == 1);

    bool r2 = false;

    if (r1) {
        Vector3f p1 = result->getPoint(0);
        r2 =  (p1.Z() == 0);
    }
    delete result;
    delete t1;
    cout<<"RESULT: "<<(r1 && r2)<<endl;
    cout<<"--------------------------TRIANGLEHIT_TEST END-----------------------------------------"<<endl;
    return r1 && r2;
}


bool toCamera_test() {
    cout<<"--------------------------TOCAMERA_TEST BEGIN-----------------------------------------"<<endl;
    Camera *cam = new Camera(Vector3f(0,0,10), Vector3f(0,1,0), Vector3f(0,0,-1));

    bool r1  = cam->toCamera(Vector3f(0, 1, 0)) == Vector3f(0, 1, 10);
    bool r2 = cam->toCamera(Vector3f(0, 0, 10)) == Vector3f(0, 0, 0);
    bool r3 = (cam->toCamera(Vector3f(0, 0, -10)) == Vector3f(0, 0, 20));
    bool r4 = cam->toCamera(Vector3f(0, 10, -10)) == Vector3f(0,10,20);

    cout<<"RESULT: "<< (r1 && r2 && r3 && r4)<<endl;
    delete cam;
    cout<<"--------------------------TOCAMERA_TEST END-----------------------------------------"<<endl;
    return r1 && r2 && r3 && r4;
}

bool cameraToWorld_test() {
    cout<<"--------------------------CAMERATOWORLD_TEST BEGIN-----------------------------------------"<<endl;
    Camera *cam = new Camera(Vector3f(0,0,10), Vector3f(0,1,0), Vector3f(0,0,-1));

    bool r1  = cam->toWorld(Vector3f(0, 1, 10)) == Vector3f(0, 1, 0);
    bool r2 = cam->toWorld(Vector3f(0, 0, 0)) == Vector3f(0, 0, 10);
    bool r3 = (cam->toWorld(Vector3f(0, 0, 20)) == Vector3f(0, 0, -10));
    bool r4 = cam->toWorld(Vector3f(0, 10, 20)) == Vector3f(0,10,-10);

    cout<<"RESULT: "<< (r1 && r2 && r3 && r4)<<endl;
    delete cam;
    cout<<"--------------------------CAMERATOWORLD_TEST END-----------------------------------------"<<endl;
    return r1 && r2 && r3 && r4;
}
