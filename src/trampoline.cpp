#include <iostream>
#include "trampoline.h"
#include "main.h"
#include "thrower.h"

Trampoline::Trampoline(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->boost = 2;
    this->rotation =0;
    static const GLfloat vertex_buffer_data[] = {
        -0.4, 0.2, 0, // vertex 1
        0.4,  0.2, 0, // vertex 2
        -0.4, -0.2, 0, // vertex 3

        0.4,  0.2, 0, // vertex 3
        -0.4, -0.2, 0, // vertex 4
        0.4, -0.2, 0 // vertex 1
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Trampoline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Trampoline::tick() {

}


bounding_box_t Trampoline::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.8, 0.4 };
    return bbox;
}

void Trampoline::landed(Thrower* thrower){
    if (detect_collision(this->bounding_box(), thrower->bounding_box()))
        thrower->speed.y = -this->boost* thrower->speed.y;
    std::cout <<"this was called" << std::endl;
  }

// For now, going to use this not so nice function
//    std::cout << thrower* bounding_box.width << std::endl;
    

