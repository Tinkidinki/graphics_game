#include "pond.h"
#include <iostream>
using namespace std;

Pond::Pond(float x)
    :Circle(x, -1, 1.0f, 0.5f, COLOR_BLACK){

    }

void Pond::tick(Thrower* thrower){
    if (in_pond(thrower)){
        cout<<"reached beyond!"<<endl;
        thrower->acceleration.y += - acc_due_to_gravity;
        
        if(escaping_from_pond(thrower)){
            float theta = atan(abs(thrower->position.y - this->position.y)
                                    /abs(thrower->position.x - this->position.x));
            float old_x_speed = thrower->speed.x;
            cout << "old speed: "<<thrower->speed.x<<","<<thrower->speed.y<< endl;
            thrower->speed.x = - thrower->speed.y * sin(theta)*cos(theta)
                                    + old_x_speed*sin(theta)*sin(theta);
            
            thrower->speed.y = thrower->speed.y * cos(theta)*cos(theta)
                                    - old_x_speed * sin(theta) * sin(theta);
            cout << "new speed: "<<thrower->speed.x<<","<<thrower->speed.y<< endl;
                                    

            thrower->acceleration.y += - thrower->speed.y;
            
            
        }

        if (escaped_from_pond(thrower)){
            //thrower->acceleration.y += - thrower->speed.y;
            thrower->speed.x = 0;
            thrower->speed.y = 0;
            thrower->position.x = this->position.x;
            thrower->position.y = this->position.y + this->radius - thrower->radius;
        }
    }
}

bool Pond::in_pond(Thrower* thrower){
    bool ans =  thrower->position.y < thrower->radius + (this->position.y) 
        && thrower->position.x > (this->position.x - this->radius)
        && thrower->position.x < (this->position.x + this->radius);
    if (ans);
       //cout<< "IN POND" << endl;

}

bool Pond::escaping_from_pond(Thrower* thrower){
    //cout<< "ESCAPE CALLED" << endl;
    float horizontal_square = pow(abs(thrower->position.x - this->position.x),2);
    float vertical_square = pow(abs(thrower->position.y - this->position.y), 2);
    float distance = sqrt(horizontal_square + vertical_square);
    //cout<< "horizontal distance square: " << horizontal_square << endl;
    //cout<< "vertical distance square" << vertical_square << endl;
    //cout<< "distance" << distance << endl;
    bool ans = distance > (this->radius - thrower->radius);
    if (ans) cout<<"ESCAPING!"<<endl;
    return ans;

}

bool Pond::escaped_from_pond(Thrower* thrower){
    float horizontal_square = pow(abs(thrower->position.x - this->position.x),2);
    float vertical_square = pow(abs(thrower->position.y - this->position.y), 2);
    float distance = sqrt(horizontal_square + vertical_square);
    bool ans = distance > (this->radius + thrower->radius);
    if (ans) cout<<"ESCAPED!"<<endl;
    return ans;

}

