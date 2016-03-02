#ifndef CAMERA_H
#define CAMERA_H

#include "vector3f.h"
#include "projection.h"

/**
 * @brief The Camera class Esta classe representa um observador virtual do mundo.
 * A imagem gerada da cena sera baseada em algum de projecao. A camera sera posicionada
 * em algum lugar na cena. Isso e indicado por meio do valor do atributo position.
 * A orientacao da camera e indicada pelos vetores up e direction. O tipo de projecao
 * e indicado pelo atributo projection.
 *
 * Para se criar um objeto do tipo Camera, procede-se como segue:
 *
 *     Camera *camera = new Camera(posicao, up, dir, projection);
 *
 *   onde posicao, up e dir sao do tipo Vector3f. Posicao, apesar de ser
 *   do tipo Vector3f, representa um ponto 3D. Up e dir sao vetores. A variavel projection
 *   eh um ponteiro para um objeto de um tipo que herda de Projection. Por exemplo:
 *
 *     Camera *camera = new Camera(Vector3f(0,0,0), Vector3f(0,1,0), Vector3f(0,0,-1), new Perspective(45, 1.0f, 0.01f));
 *
 *      representa uma camera na origem, com o lado de cima alinhado com o lado de cima da cena e apontando na direção
 *      negativa do eixo z. Essa camera realiza uma projecao perspectiva com angulo de tomada de cena de 45 gruas,
 *      razao de aspecto igual a 1.0f e  a imagem final eh projetada em um plano distante 0.01 unidades da camera.
 */
class Camera
{
    Vector3f position;
    Vector3f up;
    Vector3f direction;
    Projection *projection;
public:
    Camera(Vector3f p = Vector3f(0,0,1), Vector3f u = Vector3f(0,1,0),
           Vector3f dir = Vector3f(0,0,-1), Projection *proj=0);

    Vector3f toCamera(const Vector3f &p);
    Vector3f toWorld(const Vector3f &p);
    Vector3f project(const Vector3f &p);
    Vector3f getPosition();
    Vector3f getUp();
    Vector3f getDirection();
    Projection* getProjection();
    void setDirection(const Vector3f &dir);
    void setPosition(const Vector3f &pos);
    void setUp(const Vector3f &up);

    ~Camera();

};

#endif // CAMERA_H
