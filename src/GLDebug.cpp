#include <GLDebug.h>

void GLClearError() {
    while(glGetError() != GL_NO_ERROR);
}

int GLLogCall() {
    GLenum error = glGetError();
    if(error != GL_NO_ERROR) {
	std::cout << "[OpenGL Error: " << error << "]" << std::endl;
	return 0;
    }
    return 1;
}
