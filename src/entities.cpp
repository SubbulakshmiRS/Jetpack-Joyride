#include "entities.h"
#include "main.h"


Magnet::Magnet(int scene) {
    float x=1.0f,y=1.0f;
    this->position = glm::vec3(x, y, 0);
    this->rotation = -30.0f;
    this->radius =1.0f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data1[] = {
        0.1f,0,0,
        0,0.2f,0,
        -0.1f,0,0,
    };
    GLfloat vertex_buffer_data2[] = {
        0.1f,0,0,
        -0.1f,0,0,
        0,-0.2f,0,
    };

    this->object1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_RED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_DEAD_BLACK, GL_FILL);

}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

int Magnet::move(float x , float y){

    this->position.x += x;
    this->position.y += y;
    // check if the item is within the boundaries of the screen ( += 10 all sides)
    return 0;
}

Boost::Boost(int scene) {
    color_t choices[]={COLOR_BLUE,COLOR_BRIGHT_GREEN,COLOR_PINK};
    float x=-1.0f,y=1.0f;
    this->position = glm::vec3(x, y, 0);
    this->speed_x = 0.1f;
    this->speed_y = 0;
    this->acc_y = 0.005f;
    this->part = Polygon(this->position.x,this->position.y,choices[rand()%3],0.1,10);

}

void Boost::draw(glm::mat4 VP) {
    this->part.draw(VP);
}

void Boost::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boost::tick(){

    this->part.position.x += this->speed_x;
    this->speed_y += this->acc_y;
    this->part.position.y -= this->speed_y;
    // check if the item is within the boundaries of the screen ( += 10 all sides)
}