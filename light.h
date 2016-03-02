#ifndef LIGHT_H
#define LIGHT_H


#include "color.h"
#include "vector3f.h"
#include <string>

using namespace std;

/**
 * @brief The LightType class
 */
class LightType {

};


/**
 * @brief The PointLight class
 */
class PointLight : public LightType {
public:
    Vector3f position; //posicao da fonte de luz
    PointLight(const Vector3f &p = Vector3f(0.0f, 15, 0.0f));
};


/**
 * @brief The Light class
 */
class Light
{
    Color intensity; //cor da luz
    LightType *type; //tipo da luz
    string name; //nome da luz - pode ser utilizado para depuracao

public:
    /**
     * @brief Light permite construir um objeto do tipo Light especificando o
     * nome do objeto, o tipo de luiz e a cord da luz.
     * @param name Nome da fonte de luz (valor padrao = "default"
     * @param type Tipo de luz (valor padrao = new PointLight)
     * @param i Intensidade (valor padrao = Color (255, 255, 255)
     */
    Light(string name="default", LightType *type=new PointLight, const Color &i=Color(255, 255, 255));

    /**
     * @brief getType retorna o tipo de fonte de luz. Deve ser utilizado para obter ou
     * alterar as propriedades da fonte de luz.
     * @return LightType um objeto que representa o tipo de luz.
     */
    LightType* getType();

    /**
     * @brief getName Retorna o nome da fonte-de-luz.
     * @return string que representa o nome da fonte-de-luz.
     */
    string getName();

    /**
     * @brief getColor retorna a cor que representa a intensidade da fonte-de-luz.
     * @return Color
     */
    Color getColor();

    ~Light();
};

#endif // LIGHT_H
