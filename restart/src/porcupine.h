#include "main.h"
#include "circle.h"
#include "thrower.h"

#ifndef PORCUPINE_H
#define PORCUPINE_H

class Porcupine{
    public:
        Porcupine(){};
        Porcupine(float x);
        void tick(Thrower* thrower);
        void draw(glm::mat4 VP);
        bool touched_porcupine(Thrower* thrower);
        bool is_within_horizontal_boundary();

        Circle c1;
        Circle c2;
        Circle c3;
        glm::vec3 position;
        float radius;
        float speed;
};

#endif //PORCUPINE_H