#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vertexBuffer.h>

vertexBuffer::vertexBuffer(
		unsigned int size) {
}

vertexBuffer::vertexBuffer(
		unsigned int size, float *data) {
    glGenBuffers(1, &mID);
    glActiveTexture(GL_TEXTURE0);
    glBindBuffer(GL_ARRAY_BUFFER, mID);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
}

void vertexBuffer::bind() {
    glActiveTexture(GL_TEXTURE0);
    glBindBuffer(GL_ARRAY_BUFFER, mID);
}

void vertexBuffer::unBind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

vertexBuffer::~vertexBuffer() {
    glDeleteBuffers(1, &mID);
}
