#include "main.h"
#include "trampoline.h"

Trampoline::Trampoline(float x, float boost)
    :Rectangle(x, -0.75f, 0.5f, 1.5f, 0.0f, COLOR_RED){
        this->boost = boost;
    }

void Trampoline::tick(Thrower* thrower){
    if(detect_collision(this->bounding_box(), thrower->bounding_box())){
        thrower->speed.y = -this->boost*thrower->speed.y;
        thrower->speed.x = - thrower->speed.x;
    }
}