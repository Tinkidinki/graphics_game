#include "main.h"
#include "rectangle.h"
#include "flyer.h"

#ifndef FLYER_WITH_PLANK_H
#define FLYER_WITH_PLANK_H

class FlyerWithPlank: public Rectangle, public Flyer{
    public:
        FlyerWithPlank(){};
        FlyerWithPlank(float x, float y, float radius, float speed);
        void tick(Thrower* thrower);
        void draw(glm::mat4 VP);
        bool hit_plank(Thrower* thrower);
};

#endif //FLYER_WITH_PLANK_H
