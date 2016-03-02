#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "raycastingresult.h"
#include "ray3f.h"
#include "vector3f.h"
#include "material.h"
#include "color.h"
#include <string>

using namespace std;

/**
 * @brief The Object3D class
 */
class Object3D
{
public:

    /**
     * @brief hit Indica se o raio 'ray' intersectou algum objeto, retornando o resultado em um objeto
     * do tipo RayCastingResult.
     * @param ray O raio a ser testado.
     * @param result O resultado da interseccao. Se nao ocorrer nenhuma interseccao,
     * o resultado de result->size() é igual a zero.
     * @return
     */
    virtual RayCastingResult* hit(const Ray3f &ray, RayCastingResult *result=0)  = 0;

    /**
     * @brief getNormal Obtem a normal do objeto no ponto indicado por 'point'.
     * @param point O ponto no qual a normal sera calculada.
     * @return A normal do objeto
     */
    virtual Vector3f getNormal(const Vector3f &point) = 0;

    /**
     * @brief getNormal retorna a normal do objeto em objetos planos (que possuem a mesma normal ao longo de sua superficie).
     * @return A normal calculada.
     */
    virtual Vector3f getNormal() = 0;

    /**
     * @brief getMaterial retorna o material associado a superficie do objeto.
     * @return O material da superficie do objeto.
     */
    virtual Material* getMaterial() = 0;

    /**
     * @brief getName Retorna o nome do objeto. Util para depuracao.
     * @return O nome do objeto.
     */
    virtual string getName();
};

#endif // OBJECT3D_H
