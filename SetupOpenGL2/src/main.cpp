// Pozor na poradi headeru, první musí být glad.h

#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include "main.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


int main(void)
{
	if (!glfwInit()) {
		std::cerr << "Initialize of OpenGL failed (Init)" << std::endl;
		return -1;
	}

	// Tell GLFW what versin of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile 
	// So that means we only have the modern function
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// Create a windowed mode window and its OpenGL context 
	// Full Screen on primary monitor 
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	GLFWwindow* window = glfwCreateWindow(1920,1080,"My OpenGL App", primary, NULL);
	// Error check, if the window  fails to create
	if (!window) {
		std::cerr << "Initialize of OpenGL failed (Create window)" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Load GLAD son if configure OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Initialize of OpenGL failed (GladLoader)" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Spesify the viewport of OpenGL in the Window 
	// In this case the viewport goes from x = 0, y = 0, to x = 1920, y = 1080
	glViewport(0, 0, 1920, 1080);

	// Specify the color of the backround
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Clear the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	// Swap the back back buffer with to front buffer
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window)) {

		// get key 'ESC' to closed window 
		processInput(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW 
	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	//std::cout << "window size is: " << width << " x " << height << std::endl;
	// new rendering area
	glViewport(0, 0, width, height);
}