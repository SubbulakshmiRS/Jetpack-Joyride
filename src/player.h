#include "main.h"
#include "ball.h"
#include "polygon.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player() {}
    Player(int scene);
    glm::vec3 position;
    int up;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    int move(float x , float y);
    Ball part1;
    Polygon jet1,jet2;
};

#endif // PLAYER_H
