#include "ground.h"
#include "main.h"

#include <iostream>
using namespace std;

Ground::Ground(float x, float width):
    Rectangle(x,-2.5f, 3.0f, width, 0, COLOR_GREEN){
    }

void Ground::tick(Thrower* thrower){
    float normal_reaction = 0;
    if (detect_collision(this->bounding_box(), thrower->bounding_box())){
        normal_reaction = -acc_due_to_gravity;
        thrower->speed.y = 0;
        thrower->position.y = -1 + thrower->radius;
       
    }
    thrower->acceleration.y += normal_reaction;


}
