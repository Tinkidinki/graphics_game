#include "thrower.h"

void Thrower::set_acceleration(float x, float y){
    this->acceleration = glm::vec3(x, y, 0);
};

void Thrower::set_speed(float x, float y){
    this->speed = glm::vec3(x, y, 0);
};

void Thrower::tick(){

    this->speed.x += this->acceleration.x;
    this->speed.y += this->acceleration.y;

    if (this->below_ground()){
        this->set_speed(this->speed.x, 0);
        this->set_acceleration(this -> acceleration.x, 0);
        this->set_position(this->position.x, -1);
    }
    Ball::tick();
};

bool Thrower::below_ground(){
    if (this->position.y < -1)
        return true;
    else 
        return false;
};

bool Thrower::on_ground(){
    if (this->position.y == -1)
        return true;
    else 
        return false;
};