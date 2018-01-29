#include "circle.h"
#include "main.h"
#include <iostream>

#define PI 3.14159265358979323846

typedef struct {
        GLfloat x;
        GLfloat y;
        GLfloat z;
    }point;

point rotate_by(double angle, point inp_point){
    point new_point;
    new_point.x = inp_point.x*cos(angle) - inp_point.y*sin(angle);
    new_point.y = inp_point.x*sin(angle) + inp_point.y*cos(angle);
    return new_point;
};

void fill_array(int sides, float radius, int fraction, GLfloat array[]){
    double angle = 2 * PI / sides;
    
    point vertex;
    vertex.x = 0.0f;
    vertex.y = 0.0f;
    vertex.z = 0.0f;

    point oldpoint;
    oldpoint.x = 0.0f;
    oldpoint.y = radius;
    oldpoint.z = 0.0f;

    int iterations = (int)(fraction*sides);
    std::cout<< iterations <<std::endl;

    //For each triangle
    for(int i = 0; i < iterations; i++){
        // setting the vertex
        array[9*i + 0] = vertex.x;
        array[9*i + 1] = vertex.y;
        array[9*i + 2] = vertex.z;

        // setting the oldpoint
        array[9*i + 3] = oldpoint.x;
        array[9*i + 4] = oldpoint.y;
        array[9*i + 5] = oldpoint.z;

        // making the new point
        point newpoint = rotate_by(angle, oldpoint);

        // setting the new point
        array[9*i + 6] = newpoint.x;
        array[9*i + 7] = newpoint.y;
        array[9*i + 8] = newpoint.z;

        // New point is now old
        oldpoint = newpoint;
    }

};

Circle::Circle(float x, float y, float radius, float fraction, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    int sides = 50;
    this->radius = radius;
    this->fraction = fraction;
    GLfloat vertex_buffer_data[1000]; 
    fill_array(sides, radius, fraction, vertex_buffer_data);
    int num_vertices = (int)(fraction*sides)*3;
    std::cout << num_vertices <<std::endl;
     
    this->object = create3DObject(GL_TRIANGLES, num_vertices, vertex_buffer_data, color, GL_FILL);
}

void Circle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Circle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Circle::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, this->radius*2, this->radius*2};
    return bbox;
}