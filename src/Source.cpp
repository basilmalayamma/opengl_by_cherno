#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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

    std::cout << "Vertex shader: " << std::endl;
    std::cout << ss[0].str() << std::endl;

    std::cout << "Fragment shader: " << std::endl;
    std::cout << ss[1].str() << std::endl;

    shaderSource shaderSrc(ss[Vertex].str(), ss[Fragment].str());
    return shaderSrc;

}

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    std::cout << glGetString(GL_VERSION) << std::endl;

    GLenum err = glewInit();
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
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GL_UNSIGNED_INT), indices, GL_STATIC_DRAW);

    shaderSource shaderSrc = getShader("/home/basi/basi/git/opengl_by_cherno/res/shader/basic.shader");

    unsigned int program = createProgram(shaderSrc.vs, shaderSrc.fs);
    glUseProgram(program);
        
    GLint uniform_location;
    uniform_location = glGetUniformLocation(program, "u_Colour");
 
    glfwSwapInterval(4);

    GLfloat r = 0.0f;
    //Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        //Render here
        glClear(GL_COLOR_BUFFER_BIT);
        
        r += 0.1f;
        if (r >= 1.0f) {
            r = 0.0f;
        }
        glUniform4f(uniform_location, r, 0.0f, 1.0f - r, 1.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        //Swap front and back buffers
        glfwSwapBuffers(window);

        //Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
