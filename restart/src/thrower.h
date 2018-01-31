#include "main.h"
#include "circle.h"

#ifndef THROWER_H
#define THROWER_H

class Thrower: public Circle{
public:
    Thrower(){};
    Thrower(float x, float y, float radius);
    void tick();
    bool is_within_horizontal_boundary();
    bool is_above_sky();

    glm::vec3 speed;
    glm::vec3 acceleration;
    

};

#endif //CIRCLE_H