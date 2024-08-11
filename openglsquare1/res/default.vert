#version 400 core

layout(location=0)in vec3 position;
layout(location=1)in vec3 iColor;

out vec3 vColor;
uniform mat4 modelMatrix        = mat4(1.f);
uniform mat4 projectionMatrix   = mat4(1.f);
uniform mat4 viewMatrix         = mat4(1.f);

void main() {
    mat4 pm = modelMatrix*projectionMatrix*viewMatrix;
    vColor = iColor; 
    gl_Position = pm*vec4(position,1);
};