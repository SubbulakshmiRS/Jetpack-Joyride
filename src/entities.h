#include "main.h"
#include "polygon.h"

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

class Boost :public Polygon{
public:
    Boost() {}
    Boost(int scene);
    glm::vec3 position;
    float speed_x,speed_y,acc_y;
    Polygon part;
    int color;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();

};

class Water :public Polygon{
public:
    Water() {}
    Water(int scene);
    glm::vec3 position;
    Polygon part;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();

};

#endif // ENTITIES_H
