#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <GL/glew.h>

class shader {
public:
    shader(std::string file_name);
    ~shader();
    void attach();
    void detach();
    unsigned int getID();
private:
    void compileProgram(std::string, std::string);
    unsigned int compileShader(std::string, GLenum);
    unsigned int mID;
};

#endif //SHADER_H
