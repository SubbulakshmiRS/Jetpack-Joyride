#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color,float size);
    glm::vec3 position;
    float rotation;
    float size;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int type);
    int move(float x , float y);
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
