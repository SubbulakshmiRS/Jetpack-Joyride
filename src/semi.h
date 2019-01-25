#include "main.h"

#ifndef SEMI_H
#define SEMI_H


class Semi {
public:
    Semi() {}
    Semi(int scene);
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

#endif // SEMI_H
