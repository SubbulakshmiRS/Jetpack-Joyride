#include "coin.h"
#include "main.h"


Coin::Coin(int scene) {
    float available[] = {1.0f,2.5f};
    float y = (rand()%50)/100 + available[(rand()%2)] ;//check this
    float x = 3.5f;
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    float size = 0.1f;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -1*size,-1*size,0,
        size, size , 0,
        -1*size, size,0,
        -1*size,-1*size,0,
        size,-1*size,0,
        size, size , 0,//done
    };


    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);

}

void Coin::draw(glm::mat4 VP) {
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

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


