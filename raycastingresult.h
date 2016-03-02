#ifndef RAYCASTINGRESULT_H
#define RAYCASTINGRESULT_H

class Object3D;

#include <vector>
#include "vector3f.h"
#include "material.h"

using namespace std;

/**
 * @brief The RayCastingResult class Objetos desta classe representam resultados de interseccoes
 * de raio com objetos em uma cena.
 */
class RayCastingResult
{
    vector< Vector3f > points; //pontos de intersecao com o raio
    vector< float > rayPosition; //posicoes dos pontos dos objetos que intersectaram com o raio

public:
    Vector3f normal; //normal da superficie de objeto no ponto mais proximo que foi intersectado pelo raio
    Material *material; //material da superficie de objeto no ponto mais proximo que foi intersectado pelo raio
    Object3D *object; //objeto mais proximo intersectado  pelo raio

    RayCastingResult();

    /**
     * @brief size quantidade de interseccoes que ocorreram
     */
    unsigned size() const;

    /**
     * @brief getPoint retorna o n-esimo ponto intersectado
     * @param n ordem em que o ponto foi encontrado. O ponto mais proximo do inicio do raio estah em n = 0 (zero).
     * @return ponto O (n+1)-esimo ponto distante do inicio do raio.
     */
    Vector3f getPoint(int n) const; //retorna o n-esimo ponto intersectado

    /**
     * @brief getRayPosition retorna o n-esimo resultado intersectado
     * @param n ordem em que o resultado foi encontrado. O resultado mais proximo do inicio do raio estah em n = 0.
     * @return
     */
    float getRayPosition(int n) const; //retorna o n-esimo resultado intersectado

    /**
     * @brief addResult //adiciona um resultado na lista de resultados
     * @param pos Ponto intersectado
     * @param rayPosition Posicao do ponto ao longo do raio.
     */
    void addResult(Vector3f pos,   float rayPosition); //adiciona um resultado na lista de resultados
};

#endif // RAYCASTINGRESULT_H

