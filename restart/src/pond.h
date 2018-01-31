#include "main.h"
#include "circle.h"
#include "thrower.h"

#ifndef POND_H
#define POND_H

class Pond:public Circle{
    public:
        Pond(){};
        Pond(float x);
        void tick(Thrower* thrower);
        bool in_pond(Thrower* thrower);
        bool escaping_from_pond(Thrower* thrower);
        bool escaped_from_pond(Thrower* thrower);

   
};

#endif //POND_H