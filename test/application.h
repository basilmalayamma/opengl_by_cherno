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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WIDTH 640
#define HEIGHT 480
#define SHADER_PATH "../res/shader/basic.shader"
#define TEXTURE_PATH "../res/pics/spilo" 
#define TEXTURE_PATH2 "../res/pics/2.jpeg" 

float vertexData[] = {
    -0.5, -0.5, 0.0, 1.0, 0.0, 0.0,    //0
     0.5, -0.5, 1.0, 1.0, 0.0, 0.0,    //1
     0.5,  0.5, 1.0, 0.0, 0.0, 0.0,    //2
    -0.5,  0.5, 0.0, 0.0, 0.0, 0.0,    //3

     1.5, -0.5, 0.0, 1.0, 1.0, 1.0,    //0
     2.5, -0.5, 1.0, 1.0, 1.0, 1.0,    //1
     2.5,  0.5, 1.0, 0.0, 1.0, 1.0,    //2
     1.5,  0.5, 0.0, 0.0, 1.0, 1.0     //3
};

unsigned int indices1[] = {
    0, 1, 2,
    2, 3, 0,
    4, 5, 6,
    6, 7, 4
};

class Application {
public:
    Application();
    int init();
    void initializeShader(std::string path);
    int initializeBuffers();
    int initializeTexture(std::string path, std::string path2);
    unsigned int getShaderID();
    int render();
    int setupBlend();
    int setShaderValue(std::string name, int value);
    int setShaderValue(std::string name, const glm::mat4 &proj);
    ~Application();

private:
    GLFWwindow* mWindow; //need to change to shared_ptr
    std::shared_ptr<shader> mShader;
    std::shared_ptr<vertexArray> mVA;
    std::shared_ptr<indexBuffer> mIB1;
    std::shared_ptr<vertexBuffer> mVB;
    std::shared_ptr<Texture> mTexture;
    std::shared_ptr<Texture> mTexture2;
    std::shared_ptr<Renderer> mRenderer;
};

#endif //APPLICATION
