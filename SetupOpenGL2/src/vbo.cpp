#include "vbo.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	glGenBuffers(1, &ID);
	// Bind the VBO specifying its a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}