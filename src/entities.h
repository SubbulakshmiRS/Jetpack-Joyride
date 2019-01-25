#include "main.h"

#ifndef ENTITIES_H
#define ENTITIES_H


class Magnet {
public:
    Magnet() {}
    Magnet(int scene);
    glm::vec3 position;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    int move(float x , float y);
    double speed;
private:
    VAO *object1;
    VAO *object2;    
};

#endif // ENTITIES_H
