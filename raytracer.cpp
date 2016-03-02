#include "raytracer.h"
#include <QImage>
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

Raytracer::Raytracer(unsigned maxLevel)
{
    this->maxLevel = maxLevel;
}


bool equals(const Vector3f &p1, const Vector3f &p2) {
    float epslon = 1.0e-10;
    return (p2 - p1).lenght() < epslon;
}

RayCastingResult* Raytracer::testRay(const Ray3f &ray, Scene *scene) {
    float tmin = 1e20;
    float epslon = 1.0e-10;
    RayCastingResult *resultadoMaisProximo = 0;
    for (int i = 0; i < scene->countObjects(); i++) {
        Object3D *obj =  scene->getObject(i);
        RayCastingResult *result = obj->hit(ray);
        if (result->size() > 0) {
           float t = result->getRayPosition(0);
           Vector3f p = result->getPoint(0);
           if (t < tmin && t > epslon &&  !equals(p, ray.getOrigin())) {
               tmin = t;
               if (resultadoMaisProximo) {
                   delete resultadoMaisProximo;
               }
               resultadoMaisProximo = result;
           } else {
               delete result;
           }
        } else {
            delete result;
        }
    }

    return resultadoMaisProximo;
}

unsigned Raytracer::getMaxLevel() {
    return this->maxLevel;
}

void Raytracer::setMaxLevel(unsigned l) {
    this->maxLevel = l;
}


void Raytracer::sendRay(Ray3f ray, Scene *scene, Color &color, int level){
    if (!scene) {
        return;
    }

    /*TODO
     * Avalia modelo de iluminacao (envia shadow ray e, caso nao acha obstrucao para
     * fontes de luz, calcula-se a cor de incidencia direta de fonte-de-luz.
     *
     * Calcula-se raio de reflexao para computar influencia da luz oriunda de outros objetos
     *
     */

    float epslon = 1.0e-10;
    float bias   = 1.0e-4;
    RayCastingResult *resultadoMaisProximo = testRay(ray, scene);


    if (resultadoMaisProximo && (resultadoMaisProximo->getPoint(0)-ray.getOrigin()).lenght() > epslon ) {
        Ray3f shadowRay;
      /*  É um artefacto visual que aparece sob a forma de pequenos
       *  pontos negros na superfície de objectos. Por causa de alguns
       *  pequenos erros numéricos introduzidos pelo fato de que os
       * números em 3D nosso motor só pode ser representada dentro de
       * uma certa precisão, às vezes, do ponto de intersecção não é
       * exactamente directamente acima da superfície, mas ligeiramente abaixo. */

        Vector3f shadowRayOrigin = (resultadoMaisProximo->getPoint(0) + resultadoMaisProximo->normal.mult(bias));

        shadowRay.setOrigin(shadowRayOrigin);//resultadoMaisProximo->getPoint(0));

        Vector3f corfinal = color.toVector3f();
        Vector3f amb = scene->getAmbientLight().toVector3f();
        Vector3f ka = resultadoMaisProximo->material->ka.toVector3f();
        Vector3f kd = resultadoMaisProximo->material->kd.toVector3f();
        Vector3f ks = resultadoMaisProximo->material->ks.toVector3f();
        Vector3f normal = resultadoMaisProximo->normal;
        float percentualDeReflexao  = resultadoMaisProximo->material->reflectionRate;

        Vector3f d = ray.getDirection();
        float shineness = resultadoMaisProximo->material->shineness;

        corfinal = ka.mult(amb);

        for (int j = 0; j < scene->countLights(); j++){
            Light *light = scene->getLight(j);
            Vector3f lightColor = light->getColor().toVector3f();
            PointLight *lightType = reinterpret_cast<PointLight*>(light->getType());
            Vector3f lightDir = (lightType->position - shadowRay.getOrigin()).normalize();

            shadowRay.setDirection(lightDir);

            Vector3f eye = ray.getDirection().mult(-1).normalize();

            Vector3f h = (eye + lightDir).normalize();

            //printf("%f\n", max(0.0f, pow(normal.dot(h), shineness)));
            RayCastingResult *resultadoSemSombra = testRay(shadowRay, scene);
            if (!resultadoSemSombra || (resultadoMaisProximo->object == resultadoSemSombra->object ) ){

                corfinal = corfinal + lightColor.mult(kd).mult(  max(0.0f, normal.dot(lightDir) ) ) +
                         lightColor.mult(ks).mult( max(0.0f, pow(normal.dot(h), shineness) ));
            }
        }

        if (level < maxLevel) {
            Ray3f raioRefletido;
            raioRefletido.setOrigin(shadowRayOrigin);//resultadoMaisProximo->getPoint(0));
            Vector3f rdir = d - normal.mult(2 * normal.dot(d));
            raioRefletido.setDirection(rdir);

            Color corDaLuzRefletida;

            sendRay(raioRefletido, scene, corDaLuzRefletida, level+1);

            Vector3f corDaLuzRefletidaf = corDaLuzRefletida.toVector3f();

            corfinal = corfinal.mult(1-percentualDeReflexao) + corDaLuzRefletidaf.mult(percentualDeReflexao);
        }

        color.fromVector3f(corfinal);
    }
}


void Raytracer::renderer(Scene *scene, string toImagePath) {

    int width = scene->getViewportWidth();
    int height = scene->getViewportHeight();
    Projection *projection = scene->getCamera()->getProjection();
    Camera *camera = scene->getCamera();

    float deltax = projection->delta_x(width);
    float deltay = projection->delta_y(height);
    float z = projection->get_near();
    float ix = projection->get_viewportwidth()/2.0f;
    float iy = projection->get_viewportheight()/2.0f;
    Ray3f ray(Vector3f(0,0,0), Vector3f(0,0,0));

    QImage *img = new QImage(width, height, QImage::Format_RGB32);

    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {

            Color cor_do_pixel = scene->getBackground();

            //INICIO: encontra o raio que passa pelo pixel (i, j)
            float px = (-ix + deltax/2.0f + i * deltax);
            float py = (-iy + deltay/2.0f + j * deltay);

            Vector3f eye(camera->getPosition());
            Vector3f to(px, py, z);
            to = camera->toWorld(to);
            Vector3f dir = (to - eye).normalize();
            ray.setOrigin(eye);
            ray.setDirection(dir);
            //FIM: encontra o raio que passa pelo pixel (i, j)

            //INICIO: lanca o raio primario para encontrar a cor do pixel (i, j)
            sendRay(ray, scene, cor_do_pixel, 0);
            //FIM:lanca o raio primario para encontrar a cor do pixel (i, j)


            //INICIO: altera a cor do pixel na imagem final
            img->setPixel(i, j, qRgb( (int)cor_do_pixel.R, (int)cor_do_pixel.G, (int)cor_do_pixel.B));
            //cout<<(int)cor_do_pixel.R<<", "<<(int)cor_do_pixel.G<<", "<<(int)cor_do_pixel.B<<endl;
            //FIM: altera a cor do pixel na imagem final
        }
    }


    img->save(toImagePath.c_str());
    delete img;
}


Raytracer::~Raytracer() {

}
