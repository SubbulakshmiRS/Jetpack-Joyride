#include "main.h"
#include "ball.h"
#include "polygon.h"

#ifndef ENEMY_H
#define ENEMY_H

class Boomerang {
public:
    Boomerang() {}
    Boomerang(int scene);
    glm::vec3 position;
    int current;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    float points[120][2];
    void tick();
private:
    VAO *object;
};


class Beam :public Ball{
public:
    Beam() {}
    Beam(int scene);
    glm::vec3 position;
    Ball part1,part2;
    float rotation;
    time_t time;
    int direction,number;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

class Streak:public Polygon{
public:
    Streak() {}
    Streak(int scene);
    glm::vec3 position;
    Polygon part1,part2;
    float rotation;
    float c,s;
    time_t time;
    int direction,number;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

class Viserys:public Polygon{
public:
    Viserys() {}
    Viserys(int scene);
    glm::vec3 position;
    Polygon part;
    float rotation;
    std::vector<Polygon> bullets;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // ENEMY_H
