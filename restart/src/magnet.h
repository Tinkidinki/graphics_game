#include "main.h"
#include "circle.h"
#include "rectangle.h"
#include "thrower.h"


#ifndef MAGNET_H
#define MAGNET_H

class Magnet{
    public:
        Magnet(){};
        Magnet(float x, float y, float field_x, float field_y, float radius);
        void tick(Thrower* thrower);
        void draw(glm::mat4 VP);
        bool within_field(Thrower* thrower);

        Circle semicircle;
        Rectangle rec1;
        Rectangle rec2;
        
        glm::vec3 field;
        glm::vec3 position;
        float radius;
        
};

#endif //MAGNET_H