#include "main.h"
#include "rectangle.h"
#include "thrower.h"

#ifndef GROUND_H
#define GROUND_H

class Ground: public Rectangle{
public:
    Ground(){};
    Ground(float x, float width);
    void tick(Thrower* thrower);
    

private:
    VAO *object;

};

#endif //GROUND_H