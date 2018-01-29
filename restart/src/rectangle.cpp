#include "rectangle.h"
#include "main.h"
#include <iostream>
using namespace std;


Rectangle::Rectangle(float x, float y, float height, float width, float angle, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = angle;
    this->height = height;
    this->width = width;
    float vertex_h = this->height/2;
    float vertex_w = this->width/2;
   
    
    GLfloat vertex_buffer_data[] = {
        -vertex_w, -vertex_h, 0, // vertex 1
        vertex_w,  -vertex_h, 0, // vertex 2
        vertex_w,  vertex_h, 0, // vertex 3

        vertex_w,  vertex_h, 0, // vertex 3
        -vertex_w, vertex_h, 0, // vertex 4
        -vertex_w, -vertex_h, 0 // vertex 1
    };


    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}


void Rectangle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rectangle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


bounding_box_t Rectangle::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->width, this->height };
    return bbox;
}

