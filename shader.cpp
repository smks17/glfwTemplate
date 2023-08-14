#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

int success;
char error[512];

Shader::Shader(const char* _vertextFile, const char * _fragmentFile):
vertextFile(_vertextFile), fragmentFile(_fragmentFile)
{    
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const char * vertexShaderSource = readShaderSource(vertextFile);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, error);
        std::cout<<"ERROR Vertex SHADER: " << error << std::endl;
        // exit(1);
    }
    std::cout << "INFO, vertexShader is compiled!" << std::endl;

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char * fragmentShaderSource = readShaderSource(fragmentFile);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, error);
        std::cout<<"ERROR Vertex SHADER: " << error << std::endl;
        // exit(1);
    }
    std::cout << "INFO, fragmentShader is compiled!" << std::endl;

    // link the shaderProgram
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, error);
        std::cout<<"ERROR SHADER LINK: " << error << std::endl;
        // exit(1);
    }
}

const char * Shader::readShaderSource(const char * filename){
    std::ifstream file(filename, std::ios::in);
    if (!file.is_open()){
        std::cerr << "ERROR! shader file does not exist: " << filename << std::endl;
        // exit(1);
    }
    file.seekg(0,std::ios::end);
    std::streampos length = file.tellg();
    file.seekg(0,std::ios::beg);

    char * buffer = new char[length];
    file.read(&buffer[0],length);
    file.close();

    return buffer;
}

Shader::~Shader(){
    deleteShader();
}

void Shader::use(){
    glUseProgram(shaderProgram);
}

void Shader::deleteShader(){
    glDeleteProgram(shaderProgram);
}

Shader * Shader::reload(const char* _vertextFile, const char * _fragmentFile){
    //deleteShader();
    Shader * newShader = new Shader(_vertextFile, _fragmentFile);
    newShader->use();
    return newShader;
}