#include "main.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle{
public:
    Rectangle(){};
    Rectangle(float x, float y, float height, float width, float angle, color_t color);
    void set_position(float x, float y);
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
    
    glm::vec3 position;
    float rotation;
    float height;
    float width;
    

private:
    VAO *object;

};

#endif //RECTANGLE_H