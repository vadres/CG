#include "scene.h"

Scene::Scene(int vw, int vh)
{
    objects = new vector< Object3D* >();
    lights = new vector< Light* >();
    camera = new Camera(Vector3f(0,0,-10), Vector3f(0,1,0), Vector3f(0,0,1), new Perspective());
    background = Color(255, 255, 255);
    this->viewportWidth = vw;
    this->viewportHeight = vh;
    ambientColor = Color(50, 50, 50, 255);
}

Camera* Scene::getCamera() {
    return this->camera;
}

int Scene::getViewportHeight() {
    return this->viewportHeight;
}

int Scene::getViewportWidth() {
    return this->viewportWidth;
}

void Scene::setViewportWidth(int nw){
    this->viewportWidth = nw;
}

void Scene::setViewportHeight(int nh) {
    this->viewportHeight = nh;
}

void Scene::addObject(Object3D *obj) {
    this->objects->push_back(obj);
}

void Scene::addLight(Light *li){
    lights->push_back(li);
}

void Scene::removeLastLight() {
    lights->pop_back();
}

void Scene::removeLastObject() {
    objects->pop_back();
}


unsigned Scene::countLights() {
    return lights->size();
}

unsigned Scene::countObjects() {
    return objects->size();
}

Color Scene::getBackground() {
    return this->background;
}

void Scene::setBackground(const Color &c) {
    this->background = c;
}

Object3D* Scene::getObject(unsigned id) {
    return this->objects->at(id);
}

Light* Scene::getLight(unsigned id) {
    return this->lights->at(id);
}

Color Scene::getAmbientLight(){
    return this->ambientColor;
}

void Scene::setAmbientLight(Color color) {
    this->ambientColor = color;
}

Scene::~Scene() {
    if (objects) {
        delete objects;
        objects = 0;
    }

    if (lights) {
        delete lights;
        lights = 0;
    }

    if (camera) {
        delete camera;
        camera = 0;
    }
}

