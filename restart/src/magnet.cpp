#include "magnet.h"



Magnet::Magnet(float x, float y, float field_x, float field_y, float radius){
    this->field = glm::vec3(field_x, field_y,0);
    this->semicircle = Circle(x, y, 0.5f, 0.5f,-90, COLOR_RED);
    this->rec1 = Rectangle(x-0.2, y+0.375f + 0.6f,0.25f, 1.0f, 0, COLOR_RED); //hardcoded positions
    this->rec2 = Rectangle(x-0.2, y-0.375 + 0.6f,0.25f, 1.0f, 0, COLOR_RED); // this is so not what SSAD taught me
    this->radius = radius;
    this->position = glm::vec3(x, y, 0);
}

void Magnet::draw(glm::mat4 VP){
    semicircle.draw(VP);
    rec1.draw(VP);
    rec2.draw(VP);
}

void Magnet::tick(Thrower* thrower){
    if (within_field(thrower)){
        thrower->acceleration.x += this->field.x;
        thrower->acceleration.y += this->field.y;
    }

}

bool Magnet::within_field(Thrower* thrower){
    float h_dist_square = pow(abs(this->position.x - thrower->position.x), 2);
    float v_dist_square = pow(abs(this->position.y - thrower->position.y), 2);
    float dist = sqrt(h_dist_square + v_dist_square);
    return (dist < this->radius);

}
