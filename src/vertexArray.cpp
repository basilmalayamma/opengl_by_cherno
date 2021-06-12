#include <vertexArray.h>
#include <vertexBuffer.h>

vertexArray::vertexArray(int vertexSize):
	mVertexSize(vertexSize) {
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);
}

void vertexArray::enablePointer() {
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
	0, mVertexSize, GL_FLOAT, GL_FALSE,
	mVertexSize * sizeof(GL_FLOAT), (const GLvoid*)0);
}

vertexArray::~vertexArray() {
    glDisableVertexAttribArray(0);
    glDeleteVertexArrays(1, &mVAO);
}

void vertexArray::bind(void) {
    glBindVertexArray(mVAO);
}

void vertexArray::unBind(void) {
    glBindVertexArray(0);
}

int vertexArray::size() {
    return mVertexSize;
}
