#include "semi.h"
#include "main.h"


Semi::Semi(int scene) {
    float x =6.0f,y=0.5f ;
    float rotation =0;
    this->position = glm::vec3(x, y, 0);
    speed = 0.05;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    GLfloat vertex_buffer_data[18*180];
    float start_x=-2.0f,start_y=0;
    float start_inner_x=-1.8f,start_inner_y=0;
    float angle = 1.0f;
    float c,s;

    for(int i=0;i<180;i++)
    {
        vertex_buffer_data[18*i] = start_inner_x;
        vertex_buffer_data[18*i+1] = start_inner_y;
        vertex_buffer_data[18*i+2] = 0;

        vertex_buffer_data[18*i+3] = start_x;
        vertex_buffer_data[18*i+4] = start_y;
        vertex_buffer_data[18*i+5] = 0;

        vertex_buffer_data[18*i+9] = start_inner_x;
        vertex_buffer_data[18*i+10] = start_inner_y;
        vertex_buffer_data[18*i+11] = 0;

        c=cos(((i+1)*angle*M_PI)/180);
        s=sin(((i+1)*angle*M_PI)/180);

        start_inner_x = (-1.8f)*c;
        start_x = (-2.0f)*c;
        start_y = (-2.0f)*s;
        start_inner_y = (-1.8f)*s;

        vertex_buffer_data[18*i+6] = start_x;
        vertex_buffer_data[18*i+7] = start_y;
        vertex_buffer_data[18*i+8] = 0;

        vertex_buffer_data[18*i+12] = start_x;
        vertex_buffer_data[18*i+13] = start_y;
        vertex_buffer_data[18*i+14] = 0;

        vertex_buffer_data[18*i+15] = start_inner_x;
        vertex_buffer_data[18*i+16] = start_inner_y;
        vertex_buffer_data[18*i+17] = 0;
        
    }

    this->object = create3DObject(GL_TRIANGLES, 6*180, vertex_buffer_data, COLOR_BLUE, GL_FILL);
}

void Semi::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Semi::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Semi::tick(int type) {
    // type is to differentiate between the different directions of the 2 balls 
     this->rotation += type;
     //this->position.x -= type*speed;
    //this->position.y -= type*speed;
}

int Semi::move(float x , float y){

    this->position.x += x;
    this->position.y += y;
    // check if the item is within the boundaries of the screen ( += 10 all sides)
    return 0;
}
