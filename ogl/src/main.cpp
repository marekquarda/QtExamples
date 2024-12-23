#include <iostream>
#include <SDL.h>
#include "glew.h"

std::string getInfoLog(GLuint obj, 
    decltype(glGetShaderiv)const&getiv, 
    decltype(glGetShaderInfoLog)const&getinfo) 
{
    GLint infoLen;
    getiv(obj, GL_INFO_LOG_LENGTH, &infoLen);
    char* buf = new char[infoLen];
    getinfo(obj, infoLen, nullptr, buf);
    auto message = std::string("Shader Compilation failed: ") + std::string(buf);
    delete[] buf;
    throw std::runtime_error(message);
}

void throwIfShaderCompilationFailed(GLuint shader) {
    GLint status; 
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_TRUE) return;
        // GLint infoLen;
        // glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        // char* buf = new char[infoLen];
        // glGetShaderInfoLog(shader, infoLen, nullptr, buf);
        // auto message = std::string("Shader Compilation failed: ") + std::string(buf);
        // delete[] buf;
    auto message = std::string("Shader Compilation failed: ") + getInfoLog(shader, glGetShaderiv, glGetShaderInfoLog);
    throw std::runtime_error(message);
}

void throwIProgramLinkingFailed(GLuint program) {
    GLint status; 
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_TRUE) return;
        // GLint infoLen;
        // glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        // char* buf = new char[infoLen];
        // glGetProgramInfoLog(program, infoLen, nullptr, buf);
        // auto message = std::string("Program Linking failed: ") + std::string(buf);
        // delete[] buf;
     auto message = std::string("Program Linking failed: ") + getInfoLog(program, glGetProgramiv, glGetProgramInfoLog);
     throw std::runtime_error(message);
}

GLuint createShader(GLenum type, std::string const&src) {
    GLuint shader = glCreateShader(type);
    char const*srcs[] = {
        src.c_str()        
    };
    glShaderSource(shader, 1, srcs, 0);
    glCompileShader(shader);
    // check compilation shadeer
    throwIfShaderCompilationFailed(shader);
    return shader;
}

GLuint createProgram(std::string const&vs, std::string const&fs) {
    auto v = createShader(GL_VERTEX_SHADER, vs);
    auto f = createShader(GL_FRAGMENT_SHADER, fs);
    auto prg = glCreateProgram();
    
    glAttachShader(prg, v);
    glAttachShader(prg, f);
    glLinkProgram(prg);
    // check linking program
    throwIProgramLinkingFailed(prg);

    glDeleteShader(v);
    glDeleteShader(f); 

    return prg;
}

void programLog() {
    GLint version;
    glGetIntegerv(GL_VERSION, &version);
    std::cerr << "Version OpenGL: " << version << std::endl;
    std::cerr << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cerr << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cerr << "Version: " << glGetString(GL_VERSION) << std::endl;
}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    auto window = SDL_CreateWindow("OGL Windows", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, SDL_WINDOW_OPENGL);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    auto context = SDL_GL_CreateContext(window);

    glewExperimental = true;
    glewInit();
    programLog();

    auto prg = createProgram(
    // Vertex Shader = GLSL
    R".(
        #version 430

        out vec3 vColor;
        void main() {
            vColor = vec3(1);
            uint M = 20;
            uint N = 20;
            uint chl = gl_VertexID / 6;
            uint vid = gl_VertexID % 6;
            uint xOffset[6] = {
                0,1,0,0,1,1,
            };
            uint yOffset[6] = {
                0,0,1,1,0,1,
            };

            float pi = 3.1415925f;
            float ax = float((chl % N) + xOffset[vid]) / float(N) * pi * 2;
            float ay = float((chl / N) + yOffset[vid]) / float(M) * pi;

            float x = cos(ax)*sin(ay);
            float z = sin(ax)*sin(ay);
            float y = -cos(ay);
            gl_Position = vec4(x,y,z,1);
        };
    ).", 
    // Fragment shader = GLSL
    R".(
        #version 430
        in vec3 vColor;
        out vec4 fColor;

        void main() {
            fColor = vec4(vColor,1);
        };
    )."
    );
    GLuint vao;
    glCreateVertexArrays(1, &vao);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // using GLCLEARCOLORPROC = void(*)(float, float, float, float);
    // using GLCLEARPROC = void(*)(uint32_t);
    // auto glClearColor = (GLCLEARCOLORPROC) SDL_GL_GetProcAddress("glClearColor");
    // auto glClear = (GLCLEARPROC) SDL_GL_GetProcAddress("glClear");

    bool running = true;
    SDL_Event event;
    while (running)
    {
        while(SDL_PollEvent(&event)) {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            default:
                break;
            }
        }
       // glClearColor(0,0.5,0,1);    // set default frame buffer color
        glClear(GL_COLOR_BUFFER_BIT);   // clears

        glUseProgram(prg);
        glBindVertexArray(vao);

        uint32_t const M = 20;
        uint32_t const N = 20;
        glDrawArrays(GL_TRIANGLES, 0, M*N*3*2);
        //glDrawArrays(GL_POINTS, 0, M*N*3*2);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}