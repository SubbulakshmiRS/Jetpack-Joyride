#include "enemy.h"
#include "main.h"


Boomerang::Boomerang(int scene) {
    this->current =0;
    float x = 4.0f,y = 3.0f; //check the rand
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

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_DEAD_BLACK, GL_FILL);
    int i=0;
    while(x>-2.0f)
    {
        this->points[i][0]=x;
        this->points[i][1]=y;
        x-=0.15f; //40 steps
        i++;
    }
    while(x> -4.0f)
    {
        this->points[i][0]=x;
        points[i][1]=y;
        x -= 0.15f;
        y -= 0.2f;
        i++; //10 steps
    }
    while(x< -2.0f)
    {
        this->points[i][0]=x;
        points[i][1]=y;
        x += 0.15f;
        y -= 0.2f;
        i++;
    }
    while(x<4.0f)
    {
        this->points[i][0]=x;
        points[i][1]=y;
        x +=0.15f; //60 steps
        i++;
    }   

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

void Boomerang::tick() {
    this->current++;
    if (this->current >100)
        return ;
    float x= this->points[this->current][0];
    float y= this->points[this->current][1];
    this->position = glm::vec3(x, y, 0);
    
}

Beam::Beam(int scene) {
    this->time =-1;
    this->number = 0;
    this->direction = -1;
    float y = 4.0f,x=0.0f;
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->part1 = Ball(-4.0f,this->position.y,COLOR_DEAD_BLACK,0.1f,90.0f);
    this->part2 = Ball(4.0f,this->position.y,COLOR_DEAD_BLACK,0.1f,90.0f);

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -4.0f,-0.05f,0,
        4.0f,0.05f,0,
        -4.0f,0.05f,0,
        -4.0f,-0.05f,0,
        4.0f,-0.05f,0,
        4.0f,0.05f,0,
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_ORANGE, GL_FILL);

}

void Beam::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    this->part1.draw(VP);
    this->part2.draw(VP);
}

void Beam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Beam::tick() {
    if (this->position.y >= 4.0f)
        this->direction = -1;
    else if(this->position.y <= 1.0f)
        this->direction = 1;

    //this->direction = 0;
    this->position.y += this->direction*0.05f;
    float y = this->position.y;
    this->part1.position.y= this->part2.position.y = y;
    this->part1.tick(1);
    this->part2.tick(2);
}

Streak::Streak(int scene) {
    float angles[] = {30.0f,45.0f,60.0f,90.0f,120.0f,135.0f,150.0f,180.0f};
    this->time =-1;
    this->number = 0;
    this->direction = -1;
    float y = 3.0f,x=0.0f;
    this->position = glm::vec3(x, y, 0);
    this->rotation = angles[(rand()%7)];
    float c=cos((this->rotation*M_PI)/180);
    float s=sin((this->rotation*M_PI)/180);
    this->part1 = Polygon(this->position.x-(0.5f*c),this->position.y-(0.5f*s),COLOR_DEAD_BLACK,0.1f,10,0);
    this->part2 = Polygon(this->position.x+(0.5f*c),this->position.y+(0.5f*s),COLOR_DEAD_BLACK,0.1f,10,0);

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -0.5f,-0.02f,0,
        0.5f,0.02f,0,
        -0.5f,0.02f,0,
        -0.5f,-0.02f,0,
        0.5f,-0.02f,0,
        0.5f,0.02f,0,
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_LIGHT_ORANGE, GL_FILL);

}

void Streak::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    this->part1.draw(VP);
    this->part2.draw(VP);
}

void Streak::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Streak::tick() {
}

/*
Viserys::Viserys(int scene) {
    float angles[] = {30.0f,45.0f,60.0f,90.0f,120.0f,135.0f,150.0f};
    this->time =-1;
    this->number = 0;
    this->direction = -1;
    float y = 3.0f,x=0.0f;
    this->position = glm::vec3(x, y, 0);
    this->rotation = angles[(rand()%7)];
    float c=cos((this->rotation*M_PI)/180);
    float s=sin((this->rotation*M_PI)/180);
    this->part1 = Polygon(this->position.x-(0.5f*c),this->position.y-(0.5f*s),COLOR_DEAD_BLACK,0.1f,10,0);
    this->part2 = Polygon(this->position.x+(0.5f*c),this->position.y+(0.5f*s),COLOR_DEAD_BLACK,0.1f,10,0);

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -0.5f,-0.02f,0,
        0.5f,0.02f,0,
        -0.5f,0.02f,0,
        -0.5f,-0.02f,0,
        0.5f,-0.02f,0,
        0.5f,0.02f,0,
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_LIGHT_ORANGE, GL_FILL);

}

void Viserys::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    this->part1.draw(VP);
    this->part2.draw(VP);
}

void Viserys::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Viserys::tick() {
}
*/
