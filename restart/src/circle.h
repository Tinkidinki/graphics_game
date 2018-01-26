#include "main.h"

#ifndef CIRCLE_H
#define CIRCLE_H

class Circle{
public:
    Circle(){};
    Circle(float x, float y, float radius, float fraction, color_t color);
    void set_position(float x, float y);
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
    
    glm::vec3 position;
    float rotation;
    float radius;
    float fraction;
    

private:
    VAO *object;

};

#endif //CIRCLE_H