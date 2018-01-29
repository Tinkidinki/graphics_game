#include "main.h"
#include "circle.h"
#include "thrower.h"

#ifndef FLYER_H
#define FLYER_H

class Flyer: public Circle{
public:
    Flyer(){};
    Flyer(float x, float y, float radius, float speed);
    float speed;
    void tick(Thrower* thrower);
    bool is_within_horizontal_boundary();
    

private:
    VAO *object;

};

#endif //CIRCLE_H