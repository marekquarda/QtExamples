#include <SDL.h>
#include <geGL/geGL.h>
#include <geGL/StaticCalls.h>
// #include <iostream>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include "shaders.h"
// #include "bunny.h"

#define GL_COLOR_BUFFER_BIT 0x00004000        

using namespace ge::gl;
using namespace std;
//using namespace glm;


int main() { 
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * window = SDL_CreateWindow("izgOpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    init();

 //  glEnable(GL_DEPTH_TEST);
/*
    float vertices[] = {
        // position / colors
        -1,-1,0,1, 1,0,0,
        +1,-1,0,1, 0,1,0,
        -1,+1,0,1, 0,0,1, 
        +1,+1,0,1, 1,1,1,
    };

    uint32_t indices[] = {
        0,1,2,2,1,3
    };*/

    // GLuint vbo;
    // glCreateBuffers(1,&vbo);
    // glNamedBufferData(vbo, sizeof(bunnyVertices), bunnyVertices, GL_DYNAMIC_DRAW);

    // GLuint ebo;
    // glCreateBuffers(1,&ebo);
    // glNamedBufferData(ebo, sizeof(bunnyIndices), bunnyIndices, GL_DYNAMIC_DRAW);

    // GLuint vao;
    // glCreateVertexArrays(1, &vao);
    // // Coord
    // glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    // glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(BunnyVertex));
    // glVertexArrayAttribBinding(vao, 0,0);
    // glEnableVertexArrayAttrib(vao, 0);
    // // Colors
    // glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 0);
    // glVertexArrayVertexBuffer(vao, 1, vbo, sizeof(float)*(3), sizeof(BunnyVertex));
    // glVertexArrayAttribBinding(vao, 1,1);
    // glEnableVertexArrayAttrib(vao, 1);

    // glVertexArrayElementBuffer(vao, ebo);

    // Shaders shaderProgram("res/default.vert", "res/default.frag");
    
    // call uniform vertex shader declaration 
    // GLuint color0Location = glGetUniformLocation(prog, "color0");
    // glProgramUniform3f(prog, color0Location, 0,0,0.1);
    // mat4 T = translate(mat4(1.f), vec3(0,0,0)); 
    // mat4 P = perspective(radians(90.f),1.f,0.01f, 100.f);
    

    // GLuint modelLocation = glGetUniformLocation(shaderProgram.ID,"modelMatrix");
    // GLuint projLocation = glGetUniformLocation(shaderProgram.ID, "projectionMatrix");
    // GLuint viewLocation = glGetUniformLocation(shaderProgram.ID, "viewMatrix");
    // glProgramUniformMatrix4fv(shaderProgram.ID, modelLocation, 1, GL_FALSE, (float*)&T);
    // glProgramUniformMatrix4fv(shaderProgram.ID, projLocation, 1, GL_FALSE, (float*)&P);
    
    // //glProgramUniformMatrix4fv(prog, )
   
    // float yAngle = 0.f;
    // float xAngle = 0.f;
    // float camDistance = 3.f;
    // float sensitivity = 0.01f;
    // float zoomSpeed = 0.02f;

    // // Cutting enabled
    // glEnable(GL_CULL_FACE);

    bool running = true;
    while(running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) { 
            if (event.type == SDL_QUIT) {
                running = false;
            }
            // if(event.type==SDL_MOUSEMOTION) {
            //     if (event.motion.state & SDL_BUTTON_LMASK) {
            //         yAngle -= event.motion.xrel*sensitivity;
            //         xAngle += event.motion.yrel*sensitivity;
            //         xAngle = glm::clamp(xAngle,-glm::radians(89.f),+glm::radians(89.f));
            //     }
            //     if (event.motion.state & SDL_BUTTON_RMASK) {
            //         camDistance += event.motion.yrel*zoomSpeed;
            //         camDistance = glm::clamp(camDistance, 0.f, 100.f);
            //     }
                
     //       }
            
        }
        // shaderProgram.Activate();

        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glPointSize(10);

        // mat4 V = lookAt(vec3(sin(yAngle)*cos(xAngle),sin(xAngle),cos(yAngle)*cos(xAngle))*camDistance,vec3(0.f),vec3(0,1,0));
        // glProgramUniformMatrix4fv(shaderProgram.ID, viewLocation, 1, GL_FALSE, (float*)&V);

        // glBindVertexArray(vao); 
        // glUseProgram(shaderProgram.ID); 
        // //glDrawArrays(GL_TRIANGLES, 0, 6);
        // glDrawElements(GL_TRIANGLES, sizeof(bunnyIndices)/sizeof(VertexIndex), GL_UNSIGNED_INT,nullptr);

        SDL_GL_SwapWindow(window); 
    }

    // Delete program (shaders deleted during initialiation)
    // shaderProgram.Delete();

     SDL_GL_DeleteContext(context);
     SDL_DestroyWindow(window);
     SDL_Quit();

    return 0;
}