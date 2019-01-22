#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Boomerang {
public:
    Boomerang() {}
    Boomerang(int scene);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *object;
};

/*
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

*/
#endif // ENEMY_H
