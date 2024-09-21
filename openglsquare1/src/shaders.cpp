#include "shaders.h"

using namespace ge;

std::string get_file_contents(const char* filename) 
{
    std::ifstream in(filename, std::ios::binary);
    if (in) 
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0,std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return (contents);
    }
    throw(errno);
}

Shaders::Shaders(const char* vertexFile, const char* fragmentFile) {
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Create VertexShader Object and get reference
    GLuint vertexShader = gl::glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shder Object
    gl::glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // Compile the Vertex Shader source to the Fragment Shader Object
    gl::glCompileShader(vertexShader);
    // Check if Shader compiled successfully
    compileErrors(vertexShader, "VERTEX");

    // Create Fragment Shader Object and get its reference
    GLuint fragmentShader = gl::glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    gl::glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // Compile the Vertex Shader into machine code
    gl::glCompileShader(fragmentShader);
    // Check if Shader compileed succesfully
    compileErrors(fragmentShader, "FRAGMENT");

    // Create Shader Program Object and get its reference 
    ID = gl::glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    gl::glAttachShader(ID, vertexShader);
    gl::glAttachShader(ID, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    gl::glLinkProgram(ID);
    //std::cout << "Check program initil ... " << std::endl;
    // Check if Shaders linked sucessfully 
    compileErrors(ID, "PROGRAM");

    // Delete the now useless Vertex and Fragment Shader objects
    gl::glDeleteShader(vertexShader);
    gl::glDeleteShader(fragmentShader);
}

void Shaders::Activate() {
    gl::glUseProgram(ID);
}


void Shaders::Delete() {
    gl::glDeleteProgram(ID);
}

// Checks if the different shaders have compiled properly
void Shaders::compileErrors(unsigned int shader, const char* type) {
    GLint hasCompiled;
    char infoLog[1024];
    if (type != "PROGRAM") {
        gl::glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE) {
            gl::glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "SHADER_COMPILATION_ERROR for " << type << ": " << infoLog << std::endl;
        }
    } else {
        gl::glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE) {
            gl::glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "SHADER_LINKING_ERROR for " << type << ": " << infoLog << std::endl;
        }
    }
}