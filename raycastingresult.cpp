#include "raycastingresult.h"

RayCastingResult::RayCastingResult()
{
    this->material = 0;
    this->normal = Vector3f();
    this->object = 0;
}

unsigned RayCastingResult::size() const {
    return this->points.size();
}

Vector3f RayCastingResult::getPoint(int idx) const {
    return this->points.at(idx);
}

float RayCastingResult::getRayPosition(int idx) const {
    return this->rayPosition.at(idx);
}

void RayCastingResult::addResult(Vector3f pos,   float rayPosition) {
    this->points.push_back(pos);
    this->rayPosition.push_back(rayPosition);
}
