#include "config.h"

int main() {
    //std::cout << "Hello OpenGL" << std::endl;
    GLFWwindow* window;
    if (!glfwInit()) {
        std::cerr << "GlFW couldn't start" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(640,480,"My Window", NULL, NULL); 

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
    
    return 0;
}