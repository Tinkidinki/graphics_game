#include "main.h"
#include "thrower.h"


Thrower::Thrower(float x, float y, float radius):Circle(x, y, radius, 1.0f, 0,COLOR_RED){
    this->acceleration.x = 0; 
    this->acceleration.y = 0; //This refers to the extra acceleration apart from gravity
    this->speed.x = 0;
    this->speed.y = 0;

}

void Thrower::tick(){
    this->position.x += this -> speed.x;
    this->position.y += this -> speed.y;
    this->speed.x += this->acceleration.x;
    this->speed.y += this->acceleration.y + acc_due_to_gravity;

    if (!this->is_within_horizontal_boundary()){
        this->speed.x = -this->speed.x;
    }

    if (this->is_above_sky()){
        this->speed.y = - this->speed.y;
    }
     
}

bool Thrower::is_within_horizontal_boundary(){
    if (this->position.x <=4 and this-> position.x >=-4)
        return true;
    else 
        return false;
}

bool Thrower::is_above_sky(){
    return (this->position.y>=4);
        
}