#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

unsigned int compileShader(std::string &source, GLenum type) {
    unsigned int shader = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint vertex_compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &vertex_compiled);
    if (vertex_compiled != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(shader, 1024, &log_length, message);
        std::cout << "Error in compiling shader" << std::endl;
        std::cout << message << std::endl;
    }
    else {
        std::cout << "Compiling shader success" << std::endl;
    }

    return shader;
}

static unsigned int createProgram(std::string &vertexShader, std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cout << "Error in glewInit()" << std::endl;
        return -1;
    }
    
    float vertexData[6] = {
        -0.5,-0.5,
         0.0, 0.5,
         0.5, -0.5
    };

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    std::string vs =
        "#version 330 core\n"
        "layout(location = 0) in vec4 position;\n"
        "void main()\n"
        "{\n"
        "gl_Position = position;\n"
        "}\n";

    std::string fs =
        "#version 330 core\n"
        "layout(location = 0) out vec4 colour;\n"
        "void main()\n"
        "{\n"
        "colour = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";

    unsigned int program = createProgram(vs, fs);
    glUseProgram(program);
        
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 6 * sizeof(float));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}