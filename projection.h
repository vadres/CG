#ifndef PROJECTION_H
#define PROJECTION_H

#include "vector3f.h"

/**
 * @brief The Projection class
 */
class Projection
{
public:
    virtual Vector3f map(const Vector3f &p) = 0;
    virtual float delta_x(float hres)=0;
    virtual float delta_y(float wres)=0;
    virtual float get_near()=0;
    virtual float get_viewportwidth()=0;
    virtual float get_viewportheight()=0;
    virtual float get_fieldofview()=0;

};

#endif // PROJECTION_H
