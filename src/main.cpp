#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "coin.h"
#include "enemy.h"
#include "polygon.h"
#include "collision.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

int points;
int stop;
float max_height,max_width;

int coin_status[5];
Coin c[5];
Platform p;
Streak s;
//Polygon example;
Wall w ;
Beam b;
Ball enemy1 ;
Ball player;
Ball ball1;
Ball ball2;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
   
    //glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye ( 0,0,5 );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render

    p.draw(VP);
    w.draw(VP);
    //enemy1.draw(VP);
    //ball1.draw(VP);
    //ball2.draw(VP);
    player.draw(VP);
    for(int i=0;i<5;i++)
        if(coin_status[i] != -1)
            {
                //cout<<"hurray\n";
                c[i].draw(VP);
            }
    b.draw(VP);
    s.draw(VP);
    //example.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int zoomin = glfwGetKey(window, GLFW_KEY_Z);
    int zoomout = glfwGetKey(window, GLFW_KEY_X);



    if (left) {
        //cout<<"left";
    for(int i=0;i<5;i++)
        if(coin_status[i] != -1)
            c[i].position.x += 0.1; // move the back ground
    }
    else if (right) {
    for(int i=0;i<5;i++)
        if(coin_status[i] != -1)
        {
            c[i].position.x -= 0.1; // move the back ground
            /*if(c[i].position.x <= 5.0f) 
                coin_status[i] = -1;*/
        }
    }
    else if (up){
        if(player.position.y != 4.0f) // to stagnate at the max height
            player.position.y += 0.1;
    }
    else if(zoomin){
        screen_zoom += 0.1;
        reset_screen();
        //cout<<"zoom";
    }
    else if(zoomout){
        screen_zoom -= 0.1;
        reset_screen();
        //cout<<"out";
    }
    else 
    {
        while(player.position.y >0)
            player.position.y -= 0.1;
    }


}

void tick_elements() {
    //cout<<"tick";

    player.tick(0);
    b.tick();
    struct Point p_line[4],s_line[2];

    p_line[0] = {player.position.x+0.5f,player.position.y+0.5f};
    p_line[1] = {player.position.x+0.5f,player.position.y-0.5f};
    p_line[2] = {player.position.x-0.5f,player.position.y+0.5f};
    p_line[3] = {player.position.x-0.5f,player.position.y-0.5f};

    s_line[0] = {s.part1.position.x ,s.part1.position.y};
    s_line[1] = {s.part2.position.x ,s.part2.position.y};

    for(int i =0;i<4;i++)
    {
        if(doIntersect(p_line[i],p_line[3-i],s_line[0],s_line[1]))
        {
            cout<<"HIT BY BEAM\n";
            break;
        }
    }
    bounding_box_t p;
    p.x = player.position.x;
    p.y = player.position.y;
    p.width = 1.0f;
    p.height = 1.0f;

    for(int i=0;i<5;i++)
        if(coin_status[i] != -1)
        {
            bounding_box_t b;
            b.x = c[i].position.x;
            b.y = c[i].position.y;
            b.width = 0.2f;
            b.height = 0.2f; 
            if (detect_collision(b,p))
            {
                points += 10; // getting the coins 
                cout<<"POINTS : "<<points<<"\n";
                coin_status[i] = -1;
            }       
        }


    bounding_box_t light;
    light.x=b.position.x;
    light.y=b.position.y;
    light.width = 8.0f;
    light.height = 0.1f;
    if(detect_collision(p,light))
        cout<<"HIT\n";

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(1, 1, COLOR_RED,0.5f,0);
    ball2       = Ball(3, 3, COLOR_GREEN,1.0f,0);
    player = Ball(0, 0, COLOR_RED,0.25f,0);
    enemy1 = Ball(1, 2, COLOR_BLACK,0.5f,0);
    p = Platform(1);
    w = Wall(1);
    b = Beam(1);
    s = Streak(1);
    //example = Polygon(0,0,COLOR_BRIGHT_GREEN,0.5f,5);
    for(int i=0;i<5;i++)
        if(coin_status[i] == -1)
        {
            //cout<<"sd\n";
            c[i] = Coin(1);
            coin_status[i] = 1;
        }
        
        

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    for(int i =0;i<5;i++)
        coin_status[i] = -1;
    points = 0;
    max_height = max_width = 4.0f;
    stop = 1;
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
        for(int i=0;i<5;i++)
            if(coin_status[i] == -1)
            {
                //cout<<"sd\n";
                c[i] = Coin(1);
                coin_status[i] = 1;
            }

            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
