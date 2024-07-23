#include "ebo.h"

// Constructor that generates a Elements Buffer Object and links it to indices
EBO::EBO(GLuint* indices, GLsizeiptr size) {
	glGenBuffers(1, &ID);
	// Bind the EBO specifying its a GL_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	// Introduce the vertices into the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() {
	glDeleteBuffers(1, &ID);
}