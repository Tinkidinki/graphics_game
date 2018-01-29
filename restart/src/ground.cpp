#include "ground.h"
#include "main.h"

#include <iostream>
using namespace std;

Ground::Ground(float x, float width):
    Rectangle(x,-2.5f, 3.0f, width, 0, COLOR_GREEN){
        cout << this->height << "height of ground" << endl;
        cout << this->width << "width of ground" << endl;
    }

void Ground::tick(Thrower* thrower){
    float normal_reaction;
    if (detect_collision(this->bounding_box(), thrower->bounding_box())){
        normal_reaction = -acc_due_to_gravity;
        if (thrower->speed.y != 0)
            thrower->speed.y = 0;
        //cout << "ENTERS IF" <<endl;
        //cout << normal_reaction <<"normal_reaction inside if is"<<endl;
    }
    else{
        //normal_reaction = 0;
        //cout << normal_reaction <<"normal_reaction inside else is"<<endl;
    }
    //cout << normal_reaction <<"normal_reaction outside is"<<endl;
    
    thrower->acceleration.y += normal_reaction;
    //cout << thrower->acceleration.y <<endl;

}
