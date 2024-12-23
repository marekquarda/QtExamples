#include "SDL3/SDL.h"
#include "geGL/geGL.h"
#include "geGL/StaticCalls.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "bunny.h"

#define GL_COLOR_BUFFER_BIT     0x00004000

using namespace ge::gl;

//typedef void (*GLCLEARARCOLORPEN)(float, float, float, float);
//using GLCLEARARCOLORPEN = void(*)(float, float, float, float);
//using GLCLEARPFN        = void(*)(uint32_t);

std::string shaderTypeToName(GLuint type) {
    switch (type) 
    {
    case GL_VERTEX_SHADER:
        return "vertex";
    case GL_FRAGMENT_SHADER:
        return "fragment";   
    default:
        return "unknown";
    }
}

GLuint createShader(GLuint type, std::string const&src) {
    GLuint shader = glCreateShader(type);
    char const*shaderSrc[] = {src.c_str()};
    glShaderSource(shader, 1,shaderSrc, nullptr);
    glCompileShader(shader);
    int compileStatus;
   
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {
        char errorLog[500];
        glGetShaderInfoLog(shader, 500, nullptr, errorLog);
        SDL_Log("Compilace %s shader failed. %s",shaderTypeToName(type).c_str(), errorLog);

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
        glGetProgramInfoLog(prg, 5000, nullptr, errorLog);
    }
    return prg;
}

int main(int argc, char*argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO) != 0) {//SDL_INIT_AUDIO
         SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
         return 1;
    }
    SDL_Window *window = SDL_CreateWindow("izgOpenGL", 600, 800, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    init();

    SDL_Log("GL Version: %s", glGetString(GL_VERSION));
    SDL_Log("GL Vendor: %s", glGetString(GL_VENDOR));
    SDL_Log("GL Render: %s", glGetString(GL_RENDER));

    glEnable(GL_DEPTH_TEST);
/*
    float vertices[] = {
        -1,-1,0,1,1,0,0,
        +1,-1,0,1,0,1,0,
        -1,+1,0,1,0,0,1,
        +1,+1,0,1,1,1,1,
    };

    uint8_t indices[] = {
        0,1,2,2,1,3,
    };*/ 

    GLuint vbo;
    glCreateBuffers(1,&vbo);
    glNamedBufferData(vbo, sizeof(bunnyVertices),bunnyVertices, GL_DYNAMIC_DRAW);

    GLuint ebo;
    glCreateBuffers(1,&ebo);
    glNamedBufferData(ebo, sizeof(bunnyIndices),bunnyIndices, GL_DYNAMIC_DRAW);

    GLuint vao;
    glCreateVertexArrays(1, &vao);

    glVertexArrayAttribFormat(vao, 0,3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(BunnyVertex));
    glVertexArrayAttribBinding(vao, 0,0);    
    glEnableVertexArrayAttrib(vao, 0);

    glVertexArrayAttribFormat(vao, 1,3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, 1, vbo, sizeof(float)*3, sizeof(BunnyVertex));
    glVertexArrayAttribBinding(vao, 1,1);    
    glEnableVertexArrayAttrib(vao, 1);

    glVertexArrayElementBuffer(vao, ebo); 
      
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    
    std::string vsSrc = 
    R".(
        #version 410

        layout(location=0)in vec3 position;
        layout(location=1)in vec3 normal  ;   
        out vec3 vNormal;
        out vec3 vPosition;

        uniform mat4 modelMatrix = mat4(1.f);
        uniform mat4 projectionMatrix = mat4(1.f);
        uniform mat4 viewMatrix = mat4(1.f);

        //uniform vec3 color0 = vec3(1,0,0);
        void main() {
            mat4 mvp = modelMatrix*projectionMatrix*viewMatrix;

            gl_Position = mvp*vec4(position,1);
            vPosition = vec3(modelMatrix*vec4(position,1));
            vNormal = normal;
        }
        ).";

    std::string fsSrc = 
    R".(
        #version 410

        in vec3 vNormal;
        in vec3 vPosition;
        uniform vec3 light = vec3(10,10,10);

        out vec4 fColor;
        void main() {
            vec3 N = normalize(vNormal);
            vec3 L = normalize(light-vPosition);
            vec3 diffuseMaterial = vec3(0.2,0.5,0.7);
            vec3 lightColor = vec3(1,1,1);
            float dF = clamp(dot(N,L),0,1);
            float aF = 0.2;
            vec3 Id = dF * diffuseMaterial * lightColor;
            vec3 Ia = diffuseMaterial * aF;
            vec3 finalColor = Id + Ia;
            
            fColor = vec4(finalColor,1);
        }

    ).";
    
    // glShaderSource(vs, 1, vsSrc, nullptr);
    // glCompileShader(vs);
    // int compileStatus;
   
    // glGetShaderiv(vs, GL_COMPILE_STATUS, &compileStatus);
    // if (compileStatus != GL_TRUE) {
    //     char errorLog[500];
    //     glGetShaderInfoLog(vs, 500, nullptr, errorLog);
    //     SDL_Log("Compilace vs failed. %s", errorLog);

    // }
    GLuint vsshader = createShader(GL_VERTEX_SHADER, vsSrc);
    GLuint fsshader = createShader(GL_FRAGMENT_SHADER, fsSrc);
    GLuint prg = createProgram(vsshader, fsshader);

    // GLuint color0location = glGetUniformLocation(prg, "color0");
    // glProgramUniform3f(prg, color0location, 0.5,.2,0.1);
    glm::mat4 T = glm::translate(glm::mat4(1.f), glm::vec3(0,0,0));
    glm::mat4 P = glm::perspective(glm::radians(90.f),1.f,0.01f,100.f);
   
    GLuint matLoc = glGetUniformLocation(prg, "modelMatrix");
    glProgramUniformMatrix4fv(prg, matLoc, 1, GL_FALSE, (float*)&T);
    GLuint matPro = glGetUniformLocation(prg, "projectionMatrix");
    glProgramUniformMatrix4fv(prg, matPro, 1, GL_FALSE, (float*)&P);
    GLuint matView = glGetUniformLocation(prg, "viewMatrix");
    
    //glProgramUniform4d()

    //glm::rotate()

    // GLCLEARARCOLORPEN glClearColor = (GLCLEARARCOLORPEN) SDL_GL_GetProcAddress("glClearColor");
    // if (glClearColor != NULL) {
    //     SDL_Log("glClearColor Address: %p",(void*) glClearColor);
    // }
    // GLCLEARPFN glClear = (GLCLEARPFN) SDL_GL_GetProcAddress("glClear");

    float yAngle = 0.f;
    float sensitivity = 0.01f; 
    float xAngle = 0.f;
    float camDistance = 3.f;
    float zoomSpeed = 0.02f;

    //glEnable(GL_CULL_FACE);

    bool running = true;

    while(running) { 
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_EVENT_QUIT) {
                running = false;
            }   
            if(event.type == SDL_EVENT_MOUSE_MOTION) {
                if (event.motion.state == SDL_BUTTON_LMASK) {
                    yAngle -= event.motion.xrel * sensitivity;
                    xAngle += event.motion.yrel * sensitivity;
                    xAngle = glm::clamp(xAngle, -glm::radians(89.f), glm::radians(89.f));
                }
                if (event.motion.state == SDL_BUTTON_RMASK) {
                    camDistance += event.motion.yrel * zoomSpeed;
                    camDistance = glm::clamp(camDistance, 0.f, 1000.f);
                }
               // SDL_Log("Mouse motion postion: %f, %f", xAngle, yAngle);
            }            
        }
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPointSize(10);

        glm::mat4 V = glm::lookAt(glm::vec3(glm::sin(yAngle)*glm::cos(xAngle), glm::sin(xAngle),glm::cos(yAngle)*glm::cos(xAngle))*camDistance,glm::vec3(0.f), glm::vec3(0,1,0));
        glProgramUniformMatrix4fv(prg, matView, 1, GL_FALSE, (float*)&V);

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