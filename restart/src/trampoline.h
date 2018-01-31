#include "main.h"
#include "rectangle.h"
#include "thrower.h"

#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H

class Trampoline: public Rectangle{
public:
    Trampoline(){};
    Trampoline(float x, float boost);
    void tick(Thrower* thrower);

    float boost;

};

#endif // TRAMPOLINE_H