// Pozor na poradi headeru, první musí být glad.h
#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <stb_image.h>

#include "shaders.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "texture.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Vertical coordinates
GLfloat vertices[] =
{ //     COORDINATES	 /       COLORS      /   TexCoord // 
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f,  0.0f,	0.0f, 0.0f, // lower left corner
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,  0.0f,	0.0f, 1.0f,	// upper left corner
	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f,  1.0f,	1.0f, 1.0f,	// upper rigth corner
	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f,  1.0f,	1.0f, 0.0f	// lower left corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1,	// upper triangle
	0, 3, 2		// lower triangle
};


int main(void)
{
	// Initialize GLFW
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

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("res/default.vert", "res/default.frag");

	// Generate Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indicates
	EBO EBO1(indices, sizeof(indices));

	// Links VBO atributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Get ID of uniform called 'scale'
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture 
	Texture popCat("textures/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	// Main while loop
	while (!glfwWindowShouldClose(window)) {

		// Specify the color of the backround
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clear the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Assinns a value to the uniform; NOTE: Must alway be done after activation the Shader Program
		glUniform1f(uniID, 0.5f);
		// Binds texture so that is appears in rendering
		popCat.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back back buffer with to front buffer
		glfwSwapBuffers(window);
		// get key 'ESC' to closed window 
		processInput(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popCat.Delete();
	shaderProgram.Delete();

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