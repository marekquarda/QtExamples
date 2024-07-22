// Pozor na poradi headeru, první musí být glad.h

#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include "main.h"

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


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

	// Vertical coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	// lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		// lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	// Upper corner
		- 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	// inner left 
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,		// inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f	        // inner down

	};

	GLuint indices[] =
	{
		0, 3, 5,	// lower left triangle
		3, 2, 4,	// lower right triangle
		5, 4, 1		// Upper triangle
	};
	
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

	// Create Vertex Shader Object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader source to the Fragment Shader Object  
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Atach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program 
	glLinkProgram(shaderProgram);

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Create reference containers for the Vertex Array Object and the Vertex Buffer Object.
	GLuint VAO, VBO, EBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying its a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO  
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);
	
	// Bind both the VBO and VAO to 0 that we don't accidentally modify to VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Specify the color of the backround
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Clear the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	// Swap the back back buffer with to front buffer
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window)) {

		// Specify the color of the backround
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Clear the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use 
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw the triangle using the GL_TRIANGLES primitive 
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Swap the back back buffer with to front buffer
		glfwSwapBuffers(window);

		// get key 'ESC' to closed window 
		processInput(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteProgram(shaderProgram);

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