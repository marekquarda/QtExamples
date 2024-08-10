#ifndef TEXTURE_ID
#define TEXTURE_ID

#include <glad.h>
#include <stb_image.h>

#include "shaders.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixeltype);

	// Assigns a texture unit to a texture
	void texUnit(Shader shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
};

#endif // !TEXTURE_ID


