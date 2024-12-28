#include "SDL3/SDL.h"
#include <iostream>
#include "geGL/geGL.h"
#include "geGL/StaticCalls.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace ge::gl;

std::string shaderTypeToName(GLuint type) {
    switch (type)
    {
    case GL_VERTEX_SHADER:
        return "vs";
    case GL_FRAGMENT_SHADER:
        return "fs";
    default:
        return "unknown";
    }
}

GLuint createShader(GLuint type, std::string const&src) {
    GLuint shader = glCreateShader(type);
    char const*sSrc[]={
        src.c_str()
    };
    glShaderSource(shader, 1, sSrc, nullptr);
    glCompileShader(shader);

    // Compile log
    int compileStatus;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&compileStatus);
    if(compileStatus != GL_TRUE) {
        char errorLog[500]; 
        glGetShaderInfoLog(shader, 500, nullptr, errorLog);
        std::cerr << "Compilace " << shaderTypeToName(shader) << " selhala :" << std::endl;     
        std::cerr << errorLog << std::endl;     
    }
    return shader;
}

GLuint createProgram(GLuint vs, GLuint fs) {
    GLuint prg = glCreateProgram();
    glAttachShader(prg, vs);
    glAttachShader(prg, fs);

    glLinkProgram(prg);

    int linkStatus;
    glGetProgramiv(prg, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        char errorLog[500]; 
        glGetProgramInfoLog(prg, 500, nullptr, errorLog);
        std::cerr << "Link error: " << std::endl;    
        std::cerr << errorLog << std::endl;
    }
    return prg;
}

int main(int args, char*argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("OpenGL",800, 800,SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    init();

      float vertices[] = {
        // coord    rgb
        -1,-1,0,1,  1,0,0,
        +1,-1,0,1,  0,1,0,
        -1,+1,0,1,  0,0,1,

       // -1,+1,0,1,  0,0,1,
       // +1,-1,0,1,  0,1,0,
        +1,+1,0,1,  1,1,1
    };

    uint32_t indices[] = {
        0,1,2,2,1,3
    };

    GLuint vbo;
    glCreateBuffers(1, &vbo);
    glNamedBufferData(vbo, sizeof(float)*((4+3)*4), vertices, GL_DYNAMIC_DRAW);

    GLuint ebo;
    glCreateBuffers(1, &ebo);
    glNamedBufferData(ebo, sizeof(uint32_t)*6,indices, GL_DYNAMIC_DRAW);

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glVertexArrayAttribFormat(vao, 0, 4,GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(float)*7);
    glVertexArrayAttribBinding(vao,0,0);
    glEnableVertexArrayAttrib(vao, 0);

    glVertexArrayAttribFormat(vao, 1, 3,GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, 1, vbo, sizeof(float)*4, sizeof(float)*7);
    glVertexArrayAttribBinding(vao,1,1);
    glEnableVertexArrayAttrib(vao, 1);

    glVertexArrayElementBuffer(vao, ebo);

    std::string vsSrc =
         R".(
            #version 450

            layout(location=0)in vec4 position;
            layout(location=1)in vec3 color;

            out vec3 vColor;

            uniform mat4 modelMatrix = mat4(1.f);
            uniform mat4 viewMatrix = mat4(1.f);
            uniform mat4 projMatrix = mat4(1.f);

            void main() {
                mat4 mvp = projMatrix*modelMatrix*viewMatrix;
                vColor = color;
                gl_Position = mvp*position;
            }
         ).";            
    
    std::string fsSrc=
        R".(
            #version 450

            out vec4 fColor;
            in vec3 vColor;
            void main() {
                fColor = vec4(vColor,1);
            }
         ).";            

    GLuint vs = createShader(GL_VERTEX_SHADER, vsSrc);
    GLuint fs = createShader(GL_FRAGMENT_SHADER, fsSrc);
    GLuint prg = createProgram(vs, fs);

  //  GLuint colorLoc = glGetUniformLocation(prg, "color0");
   // glProgramUniform3f(prg,colorLoc, 0.f, 1.f, 0.f);

    GLuint modelLoc = glGetUniformLocation(prg, "modelMatrix");
    GLuint viewLoc = glGetUniformLocation(prg, "viewMatrix");
    GLuint projLoc = glGetUniformLocation(prg, "projMatrix");

    glm::mat4 T = glm::translate(glm::mat4(1.f),glm::vec3(0.5,0,0));
    glm::mat4 P = glm::perspective(glm::radians(90.f), 1.f,0.01f, 100.f);

    glProgramUniformMatrix4fv(prg, modelLoc,1, GL_FALSE, (float*)&T);
    glProgramUniformMatrix4fv(prg, projLoc,1, GL_FALSE, (float*)&P);
    

    std::cerr << glGetString(GL_VERSION) << std::endl;
    std::cerr << glGetString(GL_VENDOR) << std::endl;
    std::cerr << glGetString(GL_RENDERER) << std::endl;

    float yAngle = 0.f;
    float xAngle = 0.f;
    float sensitivity = 0.01f;
    float cameraDistance = 3.0f;
    float zoomSpeed = 0.02f;
    //float xAngle = 0.f;

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if(event.type==SDL_EVENT_QUIT) {
                running = false;
            }
            if(event.type==SDL_EVENT_MOUSE_MOTION) {
                if(event.motion.state & SDL_BUTTON_LMASK) {
                    yAngle -= event.motion.xrel*sensitivity;
                    xAngle += event.motion.yrel*sensitivity;
                    //std::cerr << "Mouse motion: " << yAngle << std::endl;
                }
                if(event.motion.state & SDL_BUTTON_RMASK) {
                    cameraDistance += event.motion.yrel*zoomSpeed;
                }
            }
        }
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(10.f);

        glm::mat4 V = glm::lookAt(glm::vec3(glm::sin(yAngle)*glm::cos(xAngle),glm::sin(xAngle),glm::cos(yAngle)*cos(xAngle))*cameraDistance, glm::vec3(0.f), glm::vec3(0,1,0));
        glProgramUniformMatrix4fv(prg, viewLoc,1, GL_FALSE, (float*)&V);

        glBindVertexArray(vao);
        glUseProgram(prg); 
        //glDrawArrays(GL_TRIANGLES, 0,6);
        glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,nullptr);

        SDL_GL_SwapWindow(window);
    }
   
    glDeleteShader(vs);
    glDeleteShader(fs);
    glDeleteProgram(prg);

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}