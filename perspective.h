#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include "vector3f.h"
#include "projection.h"

/**
 * @brief The Perspective class
 */
class Perspective : public Projection
{
    float fieldOfView;
    float aspectRatio;
    float near;
public:
    /**
     * @brief Perspective cria um objeto que pode realizar transformacoes perspectiva
     * @param fov field of view ou angulo de abertura da cena. Quando maior o valor deste
     * angulo, maior o campo de visao e os objetos na cena irao aparecer menores em relacao
     * a um angulo de abertura menor.
     * @param asp aspect ratio ou razao de aspecto e a razao entre largura e altura do viewport
     * @param n near ou plano mais proximo da camera, onde a imagem sera projetada.
     */
    Perspective(float fov=45, float asp = 1.0f, float n = 0.01f);

    /**
     * @brief map realiza a projecao do ponto p em coordenadas do mundo no plano de projecao da cena.
     * @param p ponto a ser projetado
     * @return um ponto representando o resultado da projecao
     */
    Vector3f map(const Vector3f &p);

    /**
     * @brief set Redefine os parametros da projecao
     * @param fov veja o construtor
     * @param ar veja o construtor
     * @param n veja o construtor
     */
    void set(float fov, float ar, float n);

    /**
     * @brief delta_x  retorna a distancia horizontal entre dois pixels
     * @param wres resolucao horizontal da imagem. Por exemplo, uma imagem 800x600
     * tem resolucao horizontal de 800 pixels.
     * @return distancia horizontal entre dois pixels
     */
    float delta_x(float wres);

    /**
     * @brief delta_y retorna distancia vertical entre dois pixels
     * @param hres resolucao vertical da imagem. Por exemplo, uma imagem 800x600
     * tem resolucao vertical de 600.
     * @return distancia a distancia vertical entre dois pixels.
     */
    float delta_y(float hres);

    /**
     * @brief get_near a distancia do plano de projecao (plano mais proximo do observador).
     * Apenas o que estiver depois do plano de projecao deve aparecer na projecao final.
     * @return distancia do plano de projecao.
     */
    float get_near();

    /**
     * @brief get_viewportwidth retorna largura do viewport.
     * @return  largura do viewport.
     */
    float get_viewportwidth();

    /**
     * @brief get_viewportheight retorna altura do viewport.
     * @return altura do viewport.
     */
    float get_viewportheight();

    /**
     * @brief get_fieldofview retorna o angulo de tomada de cena.
     * @return angulo de tomada de cena.
     */
    float get_fieldofview();
};

#endif // PERSPECTIVE_H
