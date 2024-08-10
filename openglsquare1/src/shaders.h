#ifndef SHADERS_H
#define SHADERS_H

#include <geGL/geGL.h>
#include <geGL/geGL.h>
#include <geGL/StaticCalls.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shaders {
public:
    // Reference ID of the Shader Program
    GLuint ID;
    // Constructor that build the Shader Program from 2 different shaders
    Shaders(const char* vertexFile, const char* fragmentFile);

    // Activate the Shader Program
    void Activate();
    // Deletes the Shader Program
    void Delete();

private:
    // Checks if the different shaders have compiled properly
    void compileErrors(unsigned int shader, const char* type);

};

#endif //SHADERS_H