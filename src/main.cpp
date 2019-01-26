#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "coin.h"
#include "enemy.h"
#include "polygon.h"
#include "collision.h"
#include "semi.h"
#include "entities.h"
#include "player.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

int safe,attract;
int stop;
float max_height,max_width,radius;
float attract_x,attract_y,attract_r;

int level ;
int coin_status[5];
int stat ;
Coin c[5];
Platform p;
int streak_status[2];
Streak s[2];
Semi sm;
Wall w ;
Boomerang bm;
Beam b;
int beads_status[5];
Boost beads[5];
Player player;
int mag_status;
Magnet mag;
int wet ;
Water water;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

float circle_point(float radius,float z,float other_coordinate)
{
    float ans = (radius*radius) - (z*z);
    if(ans<0)
    {
        safe = 0;
        return 0;
    }
    ans = sqrt(ans);
    ans *= (-1);
    ans +=  other_coordinate;
    return ans;
}

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

    if(level == 2)
    {
        if(!wet)
            water.draw(VP);
        b.draw(VP);
    }

    if(level >=3)
    {
        if(mag_status)
            mag.draw(VP);
        sm.draw(VP);
        if(bm.current <= 115)
            bm.draw(VP);
    }
    if(level>=2)
    {

        for(int i=0;i<5;i++)
        if(beads_status[i] != -1)
            {
                beads[i].draw(VP);
            }
    }
    if(level>=1)
    {
        for(int i=0;i<5;i++)
        if(coin_status[i] != -1)
            {
                c[i].draw(VP);
            }

        for(int i=0;i<2;i++)
        if(streak_status[i] != -1)
            {
                s[i].draw(VP);
            }
    }

    player.draw(VP);
}

void tick_input(GLFWwindow *window) {

    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int zoomin = glfwGetKey(window, GLFW_KEY_Z);
    int zoomout = glfwGetKey(window, GLFW_KEY_X);

    if(up)
        player.up =1;
    else
        player.up = 0;
    
    if (left) {
        float ans;
        if(safe == 1 && level >=3)
        {
            ans = circle_point(radius,player.position.x - 0.1f - sm.position.x,sm.position.y);
        }

        if(safe == 1 && level >=3)
        {
            player.position.y = ans;
        }
        
        if(level >= 3)
        {
            mag.position.x += 0.1f;
            sm.position.x += 0.1f;
            bm.tick();
            stat =0;
            bm.position.x += 0.1f;
        }        
        if(level >= 2)
        {
            for(int i=0;i<5;i++)
                if(beads_status[i] != -1)
                {
                    beads[i].position.x += 0.1; // move the back ground
                    if(beads[i].position.x <= -5.0f || beads[i].position.x >= 5.0f) 
                        beads_status[i] = -1;
                }
            water.position.x += 0.1f;
        }        
        if(level >= 1)
        {
            for(int i=0;i<5;i++)
                if(coin_status[i] != -1)
                    c[i].position.x += 0.1; // move the back ground
            for(int i=0;i<2;i++)
                if(streak_status[i] != -1)
                    s[i].position.x += 0.1;        
        }

        if(level == 2)
            water.position.x += 0.1f;
        player.distance_covered -= 0.1f;

    }
    if (right) {
        float ans;
        if(safe ==1 && level >=3)
        {
            ans = circle_point(radius,player.position.x - 0.1f - sm.position.x,sm.position.y);
        }

        if(safe == 1 && level>=3)
        {
            ans = circle_point(radius,player.position.x+0.1f-sm.position.x,sm.position.y);
            player.position.y = ans;
        }

        if(level >= 3)
        {
            mag.position.x -= 0.1f;
            sm.position.x -= 0.1f;
            bm.tick();
            stat =0;
            bm.position.x -= 0.1f;
        }       
        if(level >= 2)
        {
            for(int i=0;i<5;i++)
                if(beads_status[i] != -1)
                {
                    beads[i].position.x -= 0.1; // move the back ground
                    if(beads[i].position.x <= -5.0f || beads[i].position.x >= 5.0f) 
                        beads_status[i] = -1;
                }
        }
        
        if(level >= 1)
        {
            for(int i=0;i<5;i++)
                if(coin_status[i] != -1)
                {
                    c[i].position.x -= 0.1; // move the back ground
                    if(c[i].position.x <= -5.0f) 
                        coin_status[i] = -1;
                }
            for(int i=0;i<2;i++)
                if(streak_status[i] != -1)
                {
                    s[i].position.x -= 0.1; // move the back ground
                    if(s[i].position.x <= -5.0f) 
                        streak_status[i] = -1;
                }
        }

        if(level == 2)
            water.position.x -= 0.1f;
        player.distance_covered += 0.1f;
    }
    if (up){
        if(safe && level>= 3)
            return ;
        if(player.position.y <= 3.5f) // to stagnate at the max height
            player.position.y += 0.1;

        return ;
    }
    else if(zoomin){
        screen_zoom += 0.1;
        reset_screen();
    }
    else if(zoomout){
        screen_zoom -= 0.1;
        reset_screen();
    }

    if(level >= 3 && safe)
    return ;
    if(player.position.y >0)
        player.position.y -= 0.03f;

}

void tick_elements() {

    float square;
    bounding_box_t p;
    p.x = player.position.x;
    p.y = player.position.y;
    p.width = 1.0f;
    p.height = 1.0f;

    player.tick();
    if(level == 2)
    {
        water.tick();
        b.tick();
    }
    if(level>= 3)
    {
        if(mag.position.x <= -5.0f)
            mag_status = 0;

        square = pow((player.position.x-sm.position.x),2.0) + pow((player.position.y-sm.position.y),2.0) ;
        radius = sqrt(square);

        if(radius<=2.2f &&radius >=1.6f)
        {
            safe =1;
        }
        else 
        {   
            radius=0;
            safe=0;
        }

        square = pow((player.position.x-mag.position.x),2.0) + pow((player.position.y-mag.position.y),2.0) ;
        attract_r = sqrt(square);
        if(attract_r <= mag.radius)
        {
            attract = 1;
            float ratio = (player.position.x-mag.position.x)/(player.position.y-mag.position.y);
            attract_y = sqrt((0.05f*0.05f)/(1+pow(ratio,2.0f)));
            ratio = 1/ratio;
            attract_x = sqrt((0.05f*0.05f)/(1+pow(ratio,2.0f)));
            if((player.position.x-mag.position.x) >= 0)
                attract_x *= (-1);
            if((player.position.y-mag.position.y) <= 0)
                attract_y *= (-1);

        }
        else 
            attract =0;
    }
    if(level >= 2)
    {
        for(int i=0;i<5;i++)
        {
            beads[i].tick();
            if(beads[i].position.y <= -5.0f || beads[i].position.y >= 5.0f) 
                beads_status[i] = -1;
        }
            
    }
    if(level >= 1)
    {
        for(int i=0;i<2;i++)
            if(streak_status[i] != -1)
                s[i].tick();
    }

    if (attract && level >= 3)
    {
        player.position.y -= (attract_y);
        sm.position.x -= attract_x;
        mag.position.x -= attract_x;    
        bm.tick();
        stat =0;
        bm.position.x -= attract_x;
        for(int i=0;i<5;i++)
        {
            if(coin_status[i] != -1)
            {
                c[i].position.x -= attract_x; // move the back ground
                if(c[i].position.x <= -5.0f) 
                    coin_status[i] = -1;
            } 
            if(beads_status[i] != -1)
            {
                beads[i].position.x -= attract_x; // move the back ground
                if(beads[i].position.x <= -5.0f || beads[i].position.x >= 5.0f) 
                    beads_status[i] = -1;
            }
            for(int i=0;i<2;i++)
                if(streak_status[i] != -1)
                {
                    s[i].position.x -= 0.1; // move the back ground
                    if(s[i].position.x <= -5.0f) 
                        streak_status[i] = -1;
                }
        }
       
    }

    if(safe == 0)
    {
        if(level >= 3)
        {
            bounding_box_t b;
            b.x=bm.position.x;
            b.y=bm.position.y;
            b.width = 0.5f;
            b.height = 0.1f;
            if(detect_collision(p,b))
                cout<<"Hit by boomerang\n";
            if(stat > 100)
                {
                    bm.tick();
                    stat =0;
                }
            else
                stat++;
        }
        if(level == 2)
        {
            square = pow((player.position.x-water.position.x),2.0) + pow((player.position.y-water.position.y),2.0) ;
            radius = sqrt(square);
            if(radius <= 0.3f)
                wet =1;
            else wet =0; 
            if(wet == 0)
            {
                bounding_box_t light;
                light.x=b.position.x;
                light.y=b.position.y;
                light.width = 8.0f;
                light.height = 0.1f;
                if(detect_collision(p,light))
                {
                    cout<<"Hit by beam\n";
                    player.lives -= 1;
                }
            }

        }
        if(level >= 2)
        {

            for(int i=0;i<5;i++)
                if(beads_status[i] != -1)
                {
                    bounding_box_t b;
                    b.x = beads[i].position.x;
                    b.y = beads[i].position.y;
                    b.width = 0.2f;
                    b.height = 0.2f; 
                    if (detect_collision(b,p))
                    {
                        if(beads[i].color == 2)
                            player.lives += 1;
                        else if(beads[i].color == 1)
                            player.points += 20;
                        else
                            player.points += 10;
                        
                        cout<<"POINTS : "<<player.points<<"\n";
                        beads_status[i] = -1;
                    }       
                }
        }
        if(level >= 1)
        {
            struct Point p_line[4],s_line[2];

            p_line[0] = {player.position.x+0.5f,player.position.y+0.5f};
            p_line[1] = {player.position.x+0.5f,player.position.y-0.5f};
            p_line[2] = {player.position.x-0.5f,player.position.y+0.5f};
            p_line[3] = {player.position.x-0.5f,player.position.y-0.5f};

            for(int i=0;i<2;i++)
            if(streak_status[i]!= -1)
            {
                s_line[0] = {s[i].part1.position.x ,s[i].part1.position.y};
                s_line[1] = {s[i].part2.position.x ,s[i].part2.position.y};

                for(int i =0;i<4;i++)
                {
                    if(doIntersect(p_line[i],p_line[3-i],s_line[0],s_line[1]))
                    {
                        //cout<<"Hit streak\n";
                        player.points -= 2;
                        //cout<<"SA POINTS : "<<player.points<<"\n";
                        break;
                    }
                }
            }
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
                        player.points += 10; // getting the coins 
                        cout<<"POINTS : "<<player.points<<"\n";
                        coin_status[i] = -1;
                    }       
                }
        }

    }
}

void initGL(GLFWwindow *window, int width, int height) {

    player = Player(1);
    p = Platform(1);
    w = Wall(1);

    bm = Boomerang(1);
    sm = Semi(1);
    mag = Magnet(1);
    mag_status = 1;
    water = Water(1);
    b = Beam(1);

    for(int i=0;i<5;i++)
        if(beads_status[i] == -1)
        {
            beads[i] = Boost(1);
            beads_status[i] = 1;
        }

    for(int i=0;i<2;i++)
        if(streak_status[i] != -1)
        {
            s[i] = Streak(1);
            streak_status[i] = 1;
        }
    for(int i=0;i<5;i++)
        if(coin_status[i] == -1)
        {
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
    //all initialization 
    wet =0;
    level =1;
    safe =0;attract = 0;
    radius =0;
    stat =0;
    mag_status = 0;
    for(int i =0;i<5;i++)
    {
        coin_status[i] = -1;
        beads_status[i] = -1;
    }
    max_height = max_width = 4.0f;
    stop = 1;
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);
    reset_screen();
    
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {

        if(level >= 1)
            for(int i=0;i<2;i++)
            {
                if(streak_status[i] == -1)
                {
                    s[i] = Streak(1);
                    streak_status[i] = 1;
                }
            }
        for(int i=0;i<5;i++)
        {
            if(level >= 1)
                if(coin_status[i] == -1)
                    {
                        c[i] = Coin(1);
                        coin_status[i] = 1;
                    }
            if(level>=2)
                if(beads_status[i] == -1)
                {
                    beads[i] = Boost(1);
                    beads_status[i] = 1;
                }
        }
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            tick_elements();
            tick_input(window);
            if(player.distance_covered >= 20.0f)
            {
                level = 3;
                mag_status = 1;
                mag.position.x = 7.0f;
            }
            else if(player.distance_covered >= 10.0f)
            {
                level = 2;
            }
            else 
                level =1;
            
            cout<<"level "<<level<<"\n";
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
