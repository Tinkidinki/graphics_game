//-------------------Necessary tools----------------------------------------------
#include <vector>
#include <random>
#include "timer.h"
#include "main.h"
using namespace std;

//------------------Template Imports---------------------------------------------
#include "circle.h"
#include "rectangle.h"
#include "flyer.h"
#include "thrower.h"
#include "ground.h"
#include "flyer_with_plank.h"
#include "trampoline.h"
#include "pond.h"
#include "magnet.h"
#include "porcupine.h"

//---------------Important declarations-------------------------------------------
GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
Timer t60(1.0 / 60);


//--------------Object declarations-----------------------------------------------
Circle c1;
Circle c2;

Flyer f1;
Thrower thrower;
Ground ground;
FlyerWithPlank fp;
Trampoline t;
Pond p;
Magnet m;
Porcupine pork;

// -------------Functions----------------------------------------------------------
void draw() {
    
    //---------Don't touch---------------------------------------------------------
    reset_screen();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram (programID);
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 MVP;  

    //---------Scene render--------------------------------------------------------
    
    c1.draw(VP);
    c2.draw(VP);
    f1.draw(VP);
    ground.draw(VP);
    p.draw(VP);
    fp.draw(VP);
    t.draw(VP);
    thrower.draw(VP);
    m.draw(VP);
    pork.draw(VP);
    
}

void move(char key){
    switch(key){
        case 'l':
            thrower.speed.x += (-0.05);
            break;
            
        case 'r':
            thrower.speed.x += (0.05);
            break;

        case 'u':
            thrower.speed.y += (0.05);
            break;
    }
}

void tick_elements() {
    thrower.acceleration.x = 0;
    thrower.acceleration.y = 0;
    //-------Other tick functions here, BEFORE the thrower's tick function------------
    f1.tick(&thrower);
    ground.tick(&thrower);
    fp.tick(&thrower);
    t.tick(&thrower);
    p.tick(&thrower);
    m.tick(&thrower);
    pork.tick(&thrower);
    //--------------------------------------------------------------------------------
    thrower.tick();

    
}


void initGL(GLFWwindow *window, int width, int height) {
    //-----------Create objects----------------------------------------------
        c1 = Circle(1,1,1.0f,0.5f,-90,COLOR_BLACK);
        c2 = Circle(1,1,1.0f,0.5f,0,COLOR_RED);
        f1 = Flyer(0,3,1.0f,0.01f);
        thrower = Thrower(-1,-1,0.25f);
        ground = Ground(-1,6.0f);
        fp = FlyerWithPlank(3.0f, 2.0f, 0.5f, 0.01f);
        t = Trampoline(-3.0f, 1.5f);
        p = Pond(3);
        m = Magnet(-2, 3, -0.002f, 0.002f, 3.0f);
        pork = Porcupine(0.0f);

        // thrower  = Thrower(1, -1, COLOR_GREEN);
        // tramp = Trampoline(-1,-1,COLOR_RED);

        // random_device rd; // obtain a random number from hardware
        // mt19937 eng(rd()); // seed the generator
        // uniform_int_distribution<> distr_x(-3.5, 3.5); // define the range
        // uniform_int_distribution<> distr_y(0, 3.5); 

        // for (int i=0; i<num_flyers; i++){
        //     flyers[i] = Flyer(distr_x(eng),distr_y(eng),COLOR_BLACK, 0.02);
        // }
   

    //-----------Don't touch-------------------------------------------------
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    reshapeWindow (window, width, height);
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
    int width  = 768;
    int height = 768;
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


