#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball(){};
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    glm::vec3 speed;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bool is_within_horizontal_boundary();
    bool is_underground();
    bool is_above_sky();
    
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
