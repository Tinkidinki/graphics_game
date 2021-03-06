#include <vector>
#include <random>
#include "main.h"
#include "timer.h"
#include "ball.h"
#include "thrower.h"
#include "flyer.h"
#include "trampoline.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

int num_flyers = 10;
Thrower thrower;
//Flyer flyer;
vector<Flyer> flyers(num_flyers);
Trampoline tramp;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

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
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    thrower.draw(VP);
    for (int i=0;i<num_flyers;i++){
        flyers[i].draw(VP);
    };
    tramp.draw(VP);
}

// void tick_input(GLFWwindow *window) {
//     int left  = glfwGetKey(window, GLFW_KEY_LEFT);
//     int right = glfwGetKey(window, GLFW_KEY_RIGHT);
//     if (left) {
//         thrower.set_speed(-0.02, thrower.speed.y);
//     }
//     else if (right) {
//         thrower.set_speed(0.02, thrower.speed.y);
//     }
// }

void tick_elements() {
    thrower.tick();

      if (detect_collision(tramp.bounding_box(), thrower.bounding_box())) {
            thrower.speed.y = -2* thrower.speed.y;
            thrower.speed.x = -thrower.speed.x;
        }

    for(int i=0;i<num_flyers;i++){
        flyers[i].tick();
    

        if (detect_collision(flyers[i].bounding_box(), thrower.bounding_box())) {
            if (thrower.speed.y < 0)
                flyers[i].set_position(-5,-5);
            
            thrower.speed.y = -thrower.speed.y;
        }
        
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    // ball1       = Ball(2, 0, COLOR_RED);
    // ball2       = Ball(-2, 0, COLOR_RED);
    thrower     = Thrower(1, -1, COLOR_GREEN);
    tramp = Trampoline(-1,-1,COLOR_RED);

    random_device rd; // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_int_distribution<> distr_x(-3.5, 3.5); // define the range
    uniform_int_distribution<> distr_y(0, 3.5); 

    for (int i=0; i<num_flyers; i++){
        flyers[i] = Flyer(distr_x(eng),distr_y(eng),COLOR_BLACK, 0.02);
    }
    
    // ball2.speed = -ball2.speed;

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
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            //tick_input(window);
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

void jump(){
    if (thrower.on_ground()){
        thrower.set_speed(thrower.speed.x, 0.06);
        thrower.set_acceleration(thrower.acceleration.x, -0.0005);
    }
}
