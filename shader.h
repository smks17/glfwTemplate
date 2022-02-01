#ifndef SHADER_H
#define SHADER_H

class Shader{
    private:
        unsigned int shaderProgram;
        const char* vertextFile;
        const char * fragmentFile;
    public:
        Shader(const char* _vertextFile, const char * _fragmentFile);
        ~Shader();
        void use();
        void deleteShader();
        const char* readShaderSource(const char * filename);
        Shader * reload(const char* _vertextFile, const char * _fragmentFile);
};

#endif /* SAHDER_H */
