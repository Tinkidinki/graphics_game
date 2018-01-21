#include "main.h"
#include "ball.h"

#ifndef FLYER_H
#define FLYER_H

class Flyer: public Ball{
    public:
        Flyer(){};
        Flyer(float x, float y, color_t color, float speed_given):Ball(x, y, color){
            this->speed.x = speed_given;
        };
       

};

#endif // FLYER_H