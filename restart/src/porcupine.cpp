#include "porcupine.h"
#include <iostream>
using namespace std;


Porcupine::Porcupine(float x){
    this->radius = 0.25f;
    this->position = glm::vec3(x, -1 + this->radius, 0 );
    this->c1 = Circle(this->position.x - 2*this->radius, this->position.y, this->radius, 1.0f, 0.0f, COLOR_GREEN);
    this->c2 = Circle(this->position.x , this->position.y, this->radius, 1.0f, 0.0f, COLOR_GREEN);
    this->c1 = Circle(this->position.x + 2*this->radius, this->position.y, this->radius, 1.0f, 0.0f, COLOR_GREEN);
    this->speed = 0.005;
}

void Porcupine::tick(Thrower* thrower){

    this->position.x += this->speed;

     if (!this->is_within_horizontal_boundary()){
        this->speed = -this->speed;
    }

    if (touched_porcupine(thrower)){
        // kill the player
        cout<< "touched porcupine" <<endl;
        
    }
}

bool Porcupine::is_within_horizontal_boundary(){
    return (this->position.x <=4 and this-> position.x >=-4);
}

bool Porcupine::touched_porcupine(Thrower* thrower){
    float horizontal_square = pow(abs(thrower->position.x - this->c1.position.x),2);
    float vertical_square = pow(abs(thrower->position.y - this->c1.position.y), 2);
    float distance = sqrt(horizontal_square + vertical_square);
    bool touched_c1 =  distance < (this->radius + thrower->radius);
    
    horizontal_square = pow(abs(thrower->position.x - this->c2.position.x),2);
    vertical_square = pow(abs(thrower->position.y - this->c2.position.y), 2);
    distance = sqrt(horizontal_square + vertical_square);
    bool touched_c2 =  distance < (this->radius + thrower->radius);

    horizontal_square = pow(abs(thrower->position.x - this->c3.position.x),2);
    vertical_square = pow(abs(thrower->position.y - this->c3.position.y), 2);
    distance = sqrt(horizontal_square + vertical_square);
    bool touched_c3 =  distance < (this->radius + thrower->radius);

    return (touched_c1 or touched_c2 or touched_c3);
}

void Porcupine::draw(glm::mat4 VP){
    this->c1.draw(VP);
    this->c2.draw(VP);
    this->c3.draw(VP);
}