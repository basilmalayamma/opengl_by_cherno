#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vertexBuffer.h>
#include <GLDebug.h>

class shaderSource {
public:
    shaderSource(std::string vertex, std::string fragment) {
        vs = vertex;
        fs = fragment;
    }

    std::string vs;
    std::string fs;
};

shaderSource getShader(std::string file_path) {
    std::ifstream file;
    std::string line;

    enum shaderType {
        Vertex = 0,
        Fragment = 1
    };

    file.open(file_path);
    int mode = -1;
    std::stringstream ss[2];

    while (getline(file, line)) {
        if ((line.find("shader")) != std::string::npos) {
            if ((line.find("vertex")) != std::string::npos) {
                mode = Vertex;
                continue;
            }
            else if ((line.find("fragment")) != std::string::npos) {
                mode = Fragment;
                continue;
            }       
        }
        ss[mode] << line << "\n";
    }
#if 0
    std::cout << "Vertex shader: " << std::endl;
    std::cout << ss[0].str() << std::endl;

    std::cout << "Fragment shader: " << std::endl;
    std::cout << ss[1].str() << std::endl;
#endif
    shaderSource shaderSrc(ss[Vertex].str(), ss[Fragment].str());
    return shaderSrc;

}

unsigned int compileShader(std::string &source, GLenum type) {
    unsigned int shader = glCreateShader(type);
    const char *src = source.c_str();
    GLCall(glShaderSource(shader, 1, &src, nullptr));
    GLCall(glCompileShader(shader));

    GLint vertex_compiled;
    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &vertex_compiled));
    if (vertex_compiled != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        GLCall(glGetShaderInfoLog(shader, 1024, &log_length, message));
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
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));
    return program;
}

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


    GLuint VAO;
    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glBindVertexArray(VAO));

    vertexBuffer<float> vb((unsigned int)GL_ARRAY_BUFFER, 8, &vertexData[0]);

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

    unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    vertexBuffer<unsigned int> ib(GL_ELEMENT_ARRAY_BUFFER, 6, indices);

    shaderSource shaderSrc = getShader("/home/basi/basi/git/opengl_by_cherno/res/shader/basic.shader");
    unsigned int program = createProgram(shaderSrc.vs, shaderSrc.fs);
    GLCall(glUseProgram(program));
        
    GLint uniform_location;
    GLCall(uniform_location = glGetUniformLocation(program, "u_Colour"));
 
    GLCall(glfwSwapInterval(4));

    GLfloat r = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        
        r += 0.1f;
        if (r >= 1.0f) {
            r = 0.0f;
        }
        GLCall(glUniform4f(uniform_location, r, 0.0f, 1.0f - r, 1.0f));
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }

    GLCall(glfwTerminate());
    return 0;
}
