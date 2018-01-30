#include "main.h"
#include "flyer_with_plank.h"
#include <math.h>

FlyerWithPlank::FlyerWithPlank(float x, float y, float radius, float speed)
    :Flyer(x, y, radius, speed),
    Rectangle(x - radius/2.0f, y, 1.0f, 0.1f, -45, COLOR_BLACK){

    }

void FlyerWithPlank::tick(Thrower* thrower){
    this->Flyer::tick(thrower);
    this->Rectangle::position.x = this->Flyer::position.x - this->radius/2.0f;
    this->Rectangle::position.y = this->Flyer::position.y;

    if (detect_collision(this->Rectangle::bounding_box(),thrower->bounding_box())){
        thrower->speed.x = thrower->speed.x * (sin(45*PI/180.0f) - cos(45*PI/180.0f));
        thrower->speed.y = thrower->speed.y * (cos(45*PI/180.0f) + sin(45*PI/180.0f));
    }

}

void FlyerWithPlank::draw(glm::mat4 VP){
    Flyer::draw(VP);
    Rectangle::draw(VP);
}
