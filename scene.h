#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "object3d.h"
#include "light.h"
#include "camera.h"
#include "projection.h"
#include "perspective.h"

using namespace std;

/**
 * @brief The Scene class
 */
class Scene
{
    vector< Object3D* > *objects;
    vector< Light* > *lights;
    Camera *camera;
    Color background;
    Color ambientColor;
    int viewportWidth;
    int viewportHeight;
public:
    Scene(int vw, int vh);

    int getViewportWidth();
    int getViewportHeight();

    void setViewportWidth(int nw);
    void setViewportHeight(int nh);

    Camera* getCamera();

    void addObject(Object3D *obj);
    void removeLastObject();

    void addLight(Light* li);
    void removeLastLight();

    Object3D* getObject(unsigned id);
    Light* getLight(unsigned id);

    unsigned countLights();
    unsigned countObjects();

    void setBackground(const Color &c);
    Color getBackground();

    void setAmbientLight(Color color);
    Color getAmbientLight();

    ~Scene();
};

#endif // SCENE_H
