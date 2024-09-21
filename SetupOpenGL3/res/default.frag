#version 330 core
out vec4 FragColor;

// Input the color from the Vertex Shader
in vec3 color;
// Input the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;

void main()
{
   FragColor = texture(tex0, texCoord);
}