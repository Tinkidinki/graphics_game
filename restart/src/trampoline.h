#include "main.h"
#include "rectangle.h"

#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H

class Trampoline: public Rectangle{
public:
    Trampoline(){};
    Trampoline(float x, float boost);
    void tick();

    float boost;

};

#endif // TRAMPOLINE_H