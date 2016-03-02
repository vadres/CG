#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <string>
#include "camera.h"
#include "perspective.h"
#include <vector>
#include "object3d.h"
#include "scene.h"
#include "light.h"

using namespace std;

/**
 * @brief The Raytracer class
 */
class Raytracer
{
    unsigned maxLevel;
    static Color defaultColor;
public:

    Raytracer(unsigned maxLevel=1);
    void renderer(Scene *scene, string toImagePath);
    void sendRay(Ray3f ray, Scene *scene=0, Color &color=defaultColor, int level = 0);
    RayCastingResult *testRay(const Ray3f &ray, Scene *scene);
    unsigned getMaxLevel();
    void setMaxLevel(unsigned l);

    ~Raytracer();
};



#endif // RAYTRACER_H
