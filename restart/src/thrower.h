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

    glm::vec3 speed;
    glm::vec3 acceleration;
    

private:
    VAO *object;

};

#endif //CIRCLE_H