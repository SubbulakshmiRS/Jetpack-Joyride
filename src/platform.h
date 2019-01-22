#include "main.h"

#ifndef PLATFORM_H
#define PLATFORM_H


class Platform {
public:
    Platform() {}
    Platform(int scene);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *object;
};

class Wall {
public:
    Wall() {}
    Wall(int scene);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *object;
};

#endif // PLATFORM_H
