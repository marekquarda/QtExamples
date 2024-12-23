#include "SDL3/SDL.h"
#include <iostream>
#include "geGL/geGL.h"
#include "geGL/StaticCalls.h"

using namespace ge::gl;

// typedef void (*GLCLEARARCOLORPEN)(float, float, float, float);
// using GLCLEARARCOLORPEN = void(*)(float, float, float, float);
// using GLCLEARPFN        = void(*)(uint32_t);

int main(int args, char*argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("OpenGL",800, 600,SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    // GLCLEARARCOLORPEN glClearColor = (GLCLEARARCOLORPEN) SDL_GL_GetProcAddress("glClearColor");
    // if (glClearColor != NULL) {
    //     SDL_Log("glClearColor Address: %p",(void*) glClearColor);
    // }
    // GLCLEARPFN glClear = (GLCLEARPFN) SDL_GL_GetProcAddress("glClear");

    init();

    std::cerr << glGetString(GL_VERSION) << std::endl;
    std::cerr << glGetString(GL_VENDOR) << std::endl;
    std::cerr << glGetString(GL_RENDERER) << std::endl;

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if(event.type==SDL_EVENT_QUIT) {
                running = false;
            }
        }
        glClearColor(1,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }
   
    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}