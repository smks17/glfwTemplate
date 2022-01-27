#include <iostream>
#include <fstream>

int main(){
    std::ifstream file("vertexShader.glsl");
    file.seekg(0,std::ios::end);
    unsigned int length = file.tellg();
    file.seekg(0,std::ios::beg);

    char buffer[length];
    file.read(&buffer[0],length);
    file.close();
}
