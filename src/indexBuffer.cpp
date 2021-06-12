#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <indexBuffer.h>

indexBuffer::indexBuffer(
		unsigned int size, unsigned int *data):
	mIndexCount(size) {
    glGenBuffers(1, &mID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void indexBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
}

void indexBuffer::unBind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

indexBuffer::~indexBuffer() {
    glDeleteBuffers(1, &mID);
}

int indexBuffer::count() {
    return mIndexCount;
}
