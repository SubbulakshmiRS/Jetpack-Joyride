#include "player.h"
#include "main.h"


Player::Player(int scene) {
    this->distance_covered = 0;
    this->up = 0;
    float x =0,y=0;
    this->position = glm::vec3(x, y, 0);
    this->part1 = Ball(this->position.x,this->position.y,COLOR_RED,0.25f,0);
    this->jet1 = Polygon(this->position.x,this->position.y-0.5f,COLOR_RED,0.3f,3,30.0f);
    this->jet2 = Polygon(this->position.x,this->position.y-0.85f,COLOR_LIGHT_ORANGE,0.3f,3,30.0f);
}

void Player::draw(glm::mat4 VP) {
    this->part1.draw(VP);
    if(this->up){
    this->jet2.draw(VP);
    this->jet1.draw(VP);
    }

}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::tick() {
    this->part1.position.x =this->position.x;
    this->part1.position.y =this->position.y;
    this->jet1.position.x =this->position.x;
    this->jet1.position.y =this->position.y-0.25f;
    this->jet2.position.x =this->position.x;
    this->jet2.position.y =this->position.y-0.35f;
}

int Player::move(float x , float y){

    // check if the item is within the boundaries of the screen ( += 10 all sides)
    return 0;
}
