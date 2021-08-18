#include <vertexArray.h>
#include <vertexBuffer.h>

vertexArray::vertexArray(int vertexSize):
	mVertexSize(vertexSize) {
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);
}

void vertexArray::enablePointer(GLint prgm, std::string name, int offset) {
    GLint location = glGetAttribLocation(prgm, name.c_str());
    std::cout << "Loacation for " << name << " is " << location << std::endl;
    glVertexAttribPointer(
	location, mVertexSize, GL_FLOAT, GL_FALSE,
	mVertexSize * 3 * sizeof(GL_FLOAT), (GLvoid*)(offset * sizeof(float)));
    glEnableVertexAttribArray((GLuint)location);
}

vertexArray::~vertexArray() {
    glDisableVertexAttribArray(1);
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
