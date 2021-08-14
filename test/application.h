#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vertexBuffer.h>
#include <GLDebug.h>
#include <vertexArray.h>
#include <indexBuffer.h>
#include <shader.h>
#include <renderer.h>
#include <texture.h>
#include <memory>

#define WIDTH 640
#define HEIGHT 480
#define SHADER_PATH "../res/shader/basic.shader"
#define TEXTURE_PATH "../res/pics/spilo" 

float vertexData[16] = {
    -0.5, -0.5, 0.0, 1.0,    //0
     0.5, -0.5, 1.0, 1.0,    //1
     0.5,  0.5, 1.0, 0.0,    //2
    -0.5,  0.5, 0.0, 0.0     //3
};

unsigned int indices1[3] = {
    0, 1, 2,
};

unsigned int indices2[3] = {
    2, 3, 0
};

class Application {
public:
    Application();
    int init();
    void initializeShader(std::string path);
    int initializeBuffers();
    int initializeTexture(std::string path);
    unsigned int getShaderID();
    int render();
    ~Application();

private:
    GLFWwindow* mWindow; //need to change to shared_ptr
    std::shared_ptr<shader> mShader;
    std::shared_ptr<vertexArray> mVA;
    std::shared_ptr<indexBuffer> mIB1;
    std::shared_ptr<indexBuffer> mIB2;
    std::shared_ptr<vertexBuffer> mVB;
    std::shared_ptr<Texture> mTexture;
    std::shared_ptr<Renderer> mRenderer;
};

#endif //APPLICATION
