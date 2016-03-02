#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

/**
 * @brief The Material class
 */
class Material
{

public:
    Color kd; //coeficiente de difusao
    Color ks; //coeficiente especular
    Color ka; //coeficiente de cor ambiente
    float shineness;
    float reflectionRate;
    Material(Color d=Color(200, 200, 200), Color sp=Color(200, 200, 200), Color a=Color(20, 20, 20), float s=10.0f);

};

#endif // MATERIAL_H
