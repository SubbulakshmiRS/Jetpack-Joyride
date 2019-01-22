#include "enemy.h"
#include "main.h"


Boomerang::Boomerang(int scene) {
    float x = -4.0f,y = rand(100)/100 + 1.5f; //check the rand
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -0.25,-0.05,0,
        0.25,0.05,0,
        -0.25,0.05,0,
        -0.25,-0.05,0,
        0.25,-0.05,0,
        0.25,0.05,0,
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_GREEN, GL_FILL);

}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


/*
Wall::Wall(int scene) {
    float x = 0.0f,y = 0.0f;
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -4,0,0,
        4,4,0,
        -4,4,0,
        -4,0,0,
        4,0,0,
        4,4,0,
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);

}

void Wall::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Wall::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
*/