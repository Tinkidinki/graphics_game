#include "main.h"
#include "flyer_with_plank.h"
#include <math.h>
#include <iostream>
using namespace std;

FlyerWithPlank::FlyerWithPlank(float x, float y, float radius, float speed)
    :Flyer(x, y, radius, speed),
    Rectangle(x, y, 2.0f, 0.1f, -45, COLOR_BLACK){

    }

void FlyerWithPlank::tick(Thrower* thrower){
    
    this->Rectangle::position.x = this->Flyer::position.x;
    this->Rectangle::position.y = this->Flyer::position.y;

    if (hit_plank(thrower)){
        //cout << "OLD SPEED:" << thrower->speed.x << "," << thrower->speed.y<<endl;
        float sin_theta = sin(45.0f*PI/180.0f);
        float cos_theta = cos(45.0f*PI/180.0f);
        float sin2theta = pow(sin_theta, 2);
        float cos2theta = pow(cos_theta, 2);
        float old_x_speed = thrower->speed.x;
        thrower->speed.x = (2 * thrower->speed.y * sin_theta * cos_theta)
                            + (thrower->speed.x * (cos2theta - sin2theta));
        thrower->speed.y = (2 * old_x_speed * sin_theta * cos_theta)
                            + (thrower->speed.y * (sin2theta - cos2theta));
        //cout << "NEW SPEED:" << thrower->speed.x << "," << thrower->speed.y<<endl;
    }

    this->Flyer::tick(thrower);

}

void FlyerWithPlank::draw(glm::mat4 VP){
    Flyer::draw(VP);
    Rectangle::draw(VP);
}

bool FlyerWithPlank::hit_plank(Thrower* thrower){
    float h_dist = abs(thrower->position.x - this->Rectangle::position.x);
    float v_dist = abs(thrower->position.y - this->Rectangle::position.y);
    float max_h_dist = this->Rectangle::height/sqrt(2.0f); //hacky, think of something soon
    float max_v_dist = this->Rectangle::height/sqrt(2.0f);

    if (h_dist < max_h_dist 
        && v_dist < max_v_dist 
        && (h_dist + v_dist < max_v_dist )){
        //cout << "HIT PLANK" << endl;
        return true;
    }
    else
        return false;
    
    
}
