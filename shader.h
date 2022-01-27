#ifndef SHADER_H
#define SHADER_H

class Shader{
    private:
        unsigned int shaderProgram;
    public:
        Shader(const char* vertextFile, const char * fragmentFile);
        void use();
        ~Shader();
        const char* readShaderSource(const char * filename);

};

#endif /* SAHDER_H */
