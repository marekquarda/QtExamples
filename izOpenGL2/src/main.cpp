#include "SDL3/SDL.h"
#include <iostream>
#include "geGL/geGL.h"
#include "geGL/StaticCalls.h"
#include "glm/gtc/matrix_transform.hpp"
#include "bunny.h"

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
    char const*sSrc[] = {
        src.c_str()
    };
    glShaderSource(shader, 1, sSrc, nullptr);
    glCompileShader(shader);

    // Compile Log
    int compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {
        char errorLog[500];
        glGetShaderInfoLog(shader, 500, nullptr, errorLog);
        std::cerr << "Compilace " << shaderTypeToName(type) << " selhala: " << std::endl;
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
    SDL_Window *window = SDL_CreateWindow("OpengGL Example", 800,800, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    init();

    // float vertices[] = {
    //     // coord   rgb
    //     -1,-1,0,1,  1,0,0,
    //     +1,-1,0,1,  0,1,0,
    //     -1,+1,0,1,  0,0,1,
    //     +1,+1,0,1,  1,1,1
    // };

    // uint32_t indices[] = {
    //     0,1,2,2,1,3
    // };

    glEnable(GL_DEPTH_TEST);

    GLuint vbo;
    glCreateBuffers(1, &vbo);
    glNamedBufferData(vbo, sizeof(bunnyVertices), bunnyVertices, GL_DYNAMIC_DRAW);

    GLuint ebo;
    glCreateBuffers(1, &ebo);
    glNamedBufferData(ebo, sizeof(bunnyIndices), bunnyIndices, GL_DYNAMIC_DRAW);


    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(BunnyVertex));
    glVertexArrayAttribBinding(vao, 0, 0);
    glEnableVertexArrayAttrib(vao, 0);

    glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, 1, vbo, sizeof(float)*3, sizeof(BunnyVertex));
    glVertexArrayAttribBinding(vao, 1,1);
    glEnableVertexArrayAttrib(vao, 1);

    glVertexArrayElementBuffer(vao, ebo);

    std::string vsSrc = 
        R".(
            #version 460

            layout(location=0)in vec3 position;
            layout(location=1)in vec3 normal;
            out vec3 vNormal;
            out vec3 vPosition;

            uniform mat4 modelMatrix = mat4(1.f);
            uniform mat4 viewMatrix = mat4(1.f);
            uniform mat4 projMatrix = mat4(1.f);

            void main() {
                mat4 mvp = projMatrix*modelMatrix*viewMatrix;
                vNormal = normal;
                gl_Position = mvp*vec4(position,1);
                vPosition = vec3(modelMatrix*vec4(position,1));
            }
        ).";

    std::string fsSrc = 
        R".(
            #version 450

            out vec4 fColor;
            uniform vec3 light = vec3(10,10,10);
            uniform mat4 viewMatrix = mat4(1.f);
            in vec3 vPosition;
            in vec3 vNormal;
            void main() {
                vec3 cameraPosition = vec3(inverse(viewMatrix)*vec4(0,0,0,1));

                vec3 N = normalize(vNormal);
                vec3 L = normalize(light-vPosition);
                vec3 diffuseMaterial = vec3(0.4,0.5,0.7);
                vec3 lightColor = vec3(1,1,1);
                float df = clamp(dot(N,L),0,1);
                float af = 0.2;
                vec3 ld = df*diffuseMaterial*lightColor;
                vec3 la = diffuseMaterial*af;

                vec3 V = normalize(cameraPosition -vPosition);
                vec3 R = -reflect(V,N);

                float sf = pow(clamp(dot(R,L),0,1),30);
                vec3 ls = lightColor*sf;

                vec3 finalColor = ld+la+ls;

                fColor = vec4(finalColor,1);
            }
        ).";

    GLuint vs = createShader(GL_VERTEX_SHADER, vsSrc);
    GLuint fs = createShader(GL_FRAGMENT_SHADER, fsSrc);
    GLuint prg = createProgram(vs, fs);

    GLuint modelLoc = glGetUniformLocation(prg, "modelMatrix");
    GLuint viewLoc = glGetUniformLocation(prg, "viewMatrix");
    GLuint projLoc = glGetUniformLocation(prg, "projMatrix");

    glm::mat4 T = glm::translate(glm::mat4(1.f), glm::vec3(0.5,0,0));
    glm::mat4 P = glm::perspective(glm::radians(90.f), 1.f,0.01f, 100.f);

    glProgramUniformMatrix4fv(prg, modelLoc, 1, GL_FALSE, (float*)&T);
    glProgramUniformMatrix4fv(prg, projLoc, 1, GL_FALSE, (float*)&P);

    std::cerr << glGetString(GL_VERSION) << std::endl;
    std::cerr << glGetString(GL_VENDOR) << std::endl;
    std::cerr << glGetString(GL_RENDERER) << std::endl;

    float yAngle = 0.f;
    float xAngle = 0.f;
    float sensitivity = 0.01f;
    float cameraDistance = 3.0f;
    float zoomSpeed = 0.02f;

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if (event.type == SDL_EVENT_MOUSE_MOTION) {
                if (event.motion.state & SDL_BUTTON_LMASK) {
                    yAngle -= event.motion.xrel*sensitivity;
                    xAngle += event.motion.yrel*sensitivity;
                    xAngle = glm::clamp(xAngle,-glm::radians(89.f),glm::radians(89.f));
                }
                if (event.motion.state & SDL_BUTTON_RMASK) {
                    cameraDistance += event.motion.yrel*zoomSpeed;
                    cameraDistance = glm::clamp(cameraDistance, 0.f,100.f);
                }
            }
        }
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPointSize(10.f);

        glm::mat4 V = glm::lookAt(glm::vec3(glm::sin(yAngle)*glm::cos(xAngle), glm::sin(xAngle), glm::cos(yAngle)*cos(xAngle))*cameraDistance, glm::vec3(0.f), glm::vec3(0,1,0));
        glProgramUniformMatrix4fv(prg, viewLoc, 1, GL_FALSE, (float*)&V);

        glBindVertexArray(vao);
        glUseProgram(prg);
        glDrawElements(GL_TRIANGLES, sizeof(bunnyIndices)/sizeof(VertexIndex), GL_UNSIGNED_INT, nullptr);

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