#include "main.h"
#include "flyer.h"
#include "thrower.h"
#include <iostream>

Flyer::Flyer(float x, float y, float radius, float speed):Circle(x, y, radius, 1.0f, COLOR_GREEN){
    this->speed = speed;
}

void Flyer::tick(Thrower* thrower){
    this->position.x +=this -> speed;

     if (!this->is_within_horizontal_boundary()){
        this->speed = -this->speed;
    }

    if (hit_flyer(thrower)){
        //std::cout << "collision!" << std::endl;
        if (thrower->speed.y <0){
            this->position.y = -5;
            this->position.x = -5;
            this->speed = 0;
        }
        
        thrower->speed.x = - thrower->speed.x;
        thrower->speed.y = - thrower->speed.y;
            
    }
}

bool Flyer::is_within_horizontal_boundary(){
    if (this->position.x <=4 and this-> position.x >=-4)
        return true;
    else 
        return false;
}

bool Flyer::hit_flyer(Thrower* thrower){
    float horizontal_square = pow(abs(thrower->position.x - this->position.x),2);
    float vertical_square = pow(abs(thrower->position.y - this->position.y), 2);
    float distance = sqrt(horizontal_square + vertical_square);
    return distance < (this->radius + thrower->radius);
}