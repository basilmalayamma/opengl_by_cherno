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

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
    GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
    GLCall(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));
    GLCall(glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE));

    GLCall(window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL));
    if (!window)
    {
        GLCall(glfwTerminate());
        return -1;
    }

    GLCall(glfwMakeContextCurrent(window));

    std::cout << glGetString(GL_VERSION) << std::endl;

    GLCall(GLenum err = glewInit());
    if (err != GLEW_OK) {
        std::cout << "Error in glewInit()" << std::endl;
        return -1;
    }
    
    float vertexData[12] = {
        -0.5,  0.5,     //0
        -0.5, -0.5,     //1
         0.5, -0.5,     //2
         0.5,  0.5,     //3
    };

    vertexArray va(2);
    vertexBuffer vb(8, &vertexData[0]);
    vb.bind();
    va.enablePointer();

    unsigned int indices1[3] = {
        0, 1, 2,
    };

    unsigned int indices2[3] = {
        2, 3, 0
    };

    indexBuffer ib1(3, indices1);
    GLCall(ib1.unBind());

    indexBuffer ib2(3, indices2);
    GLCall(ib2.unBind());

    GLCall(va.unBind());
    GLCall(vb.unBind());

    shader shader1("../res/shader/basic.shader");
    shader1.attach();

    GLint uniform_location;
    GLCall(uniform_location = glGetUniformLocation(shader1.getID(), "u_Colour"));
 
    GLfloat r = 0.0f;
    Renderer renderer;

    while (!glfwWindowShouldClose(window)) {
        renderer.clear();

        if (r >= 1.0f) {
            r = 0.0f;
        }
        r += 0.2f;
        GLCall(glUniform4f(uniform_location, r, 0.0f, 1.0f - r, 1.0f));

	renderer.render(va, ib1);
	renderer.render(va, ib2);

        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }

    shader1.detach();
    GLCall(glfwTerminate());
    return 0;
}
