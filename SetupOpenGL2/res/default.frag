#version 330 core
out vec4 FragColor;

// Input the color from the Vertex Shader
in vec3 color;

void main()
{
   FragColor = vec4(color, 1.0f);
}