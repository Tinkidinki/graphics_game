#include "main.h"
#include "ball.h"

#ifndef THROWER_H
#define THROWER_H

class Thrower : public Ball{
    public:
        Thrower(){};
        Thrower(float x, float y, color_t color) 
        : Ball(x, y, color){};
        glm::vec3 acceleration;
        void set_acceleration(float x, float y);
        void set_speed(float x, float y);
        void tick();
        bool below_ground();
        bool on_ground();


};
#endif  // THROWER_H


