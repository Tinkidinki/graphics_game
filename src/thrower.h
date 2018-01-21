#include "main.h"
#include "ball.h"

#ifndef THROWER_H
#define THROWER_H

class Thrower : public Ball{
    public:
        Thrower(float x, float y, color_t color) 
        : Ball(float x, float y, color_t color){};
        glm::vec3 acceleration;
        void set_acceleration(float x, float y);
        void push_left();
        void push_right();
        void throw_up();
        void tick();
        bool on_ground();


}


#endif  // THROWER_H