#include <QImage>
#include <iostream>
#include "vector3f.h"
#include "ray3f.h"
#include "raycastingresult.h"
#include "object3d.h"
#include "sphere.h"
#include "cylinder.h"
#include "triangle.h"
#include "camera.h"
#include "perspective.h"
#include "projection.h"
#include "material.h"
#include "raytracer.h"
#include "light.h"

int main(int argc, char *argv[])
{
    Raytracer *raytracer = new Raytracer();
    //raytracer->setMaxLevel(3);
    Sphere *sphere  = new Sphere(Vector3f(0,20,0), 3.5f);

    //Altera o material do da esfera
    // kd = cor difusa
    // ka = cor ambiente
    // shineness = indice de especularidade
    sphere->getMaterial()->kd = Color(255, 0, 0);
    sphere->getMaterial()->ka = Color(50, 50, 50);
    sphere->getMaterial()->shineness = 12.0f;

    //Cria um objeto do tipo Spheres
    Cylinder *cylinder  = new Cylinder(Vector3f(5,8,12), Vector3f(5,0,22), 5, 10);

    //Altera o material do da esfera
    // kd = cor difusa
    // ka = cor ambiente
    // shineness = indice de especularidade
    cylinder->getMaterial()->kd = Color(255, 0, 0);
    cylinder->getMaterial()->ka = Color(50, 50, 50);
    cylinder->getMaterial()->shineness = 12.0f;

    Cylinder *cylinder2  = new Cylinder(Vector3f(5,12,0), Vector3f(1,0,2), 3, 10);

    //Altera o material do da esfera
    // kd = cor difusa
    // ka = cor ambiente
    // shineness = indice de especularidade
    cylinder2->getMaterial()->kd = Color(0, 0, 250);
    cylinder2->getMaterial()->ka = Color(50, 50, 50);
    cylinder2->getMaterial()->shineness = 12.0f;
    //cria um triangulo deitado no plano xz, com todos os lados iguais a 5
    float tsize = 5;
    Triangle *triangle = new Triangle(Vector3f(0.001f, 0.001f, -tsize), Vector3f(-tsize, 0.001, tsize), Vector3f(tsize, 0.001f, tsize));
    triangle->getMaterial()->kd = Color(100, 200, 10); //altera cor difusa
    triangle->getMaterial()->ka = Color(50, 50, 50); //altera cor ambiente
    triangle->getMaterial()->ks = Color(50,50, 50);
    triangle->getMaterial()->reflectionRate = 0.4; //triangulo nao reflete

    //cria uma fonte de luz
    Light *light0 = new Light("Light0");
    Light *light1 = new Light("Light0");

    //Pega o tipo da fonte de luz. Por padrão a luz é pontual,
    // ou seja, espalha a luz em todas as direções a partir de uma posição
    PointLight *type  = reinterpret_cast<PointLight*>(light0->getType());
    PointLight *type2 = reinterpret_cast<PointLight*>(light1->getType());
    //Para alterar a posicao da luz, altera-se o campo position
    type->position  = Vector3f(10, 70, -1);
    type2->position = Vector3f(10, -20, -1);

    Scene *scene = new Scene(600, 480);

    scene->setAmbientLight(Color(200, 200, 200));

    scene->setBackground(Color(255, 255, 255));

    scene->addObject(cylinder);
    scene->addObject(cylinder2);
    scene->addObject(sphere);
    scene->addLight(light0);
    scene->addLight(light1);
    scene->getCamera()->setPosition(Vector3f(0, 50, 10));
    scene->getCamera()->setDirection(Vector3f(0.0f,-1, 0.0f));
    scene->getCamera()->setUp(Vector3f(-1,0,0));

    raytracer->renderer(scene, "D:/QtProjects/ConeRayTracing/img/cilindro.jpg");
    delete raytracer;
    delete scene;

    return 0;
}
