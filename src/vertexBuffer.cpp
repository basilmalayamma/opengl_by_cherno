#include <GLDebug.h>
#include <vertexBuffer.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

template<typename T>
vertexBuffer<T>::vertexBuffer(unsigned int target, unsigned int size, T *data) {
    glGenBuffers(1, &mID);
    glBindBuffer(target, mID);
    glBufferData(target, size * sizeof(T), data, GL_STATIC_DRAW);
}

template<typename T>
bool vertexBuffer<T>::bindBuffer(GLenum target) {
    GLCall(glBindBuffer(target, mID));
}

template<typename T>
bool vertexBuffer<T>::unBindBuffer(GLenum target) {
    GLCall(glBindBuffer(target, 0));
}

template<typename T>
vertexBuffer<T>::~vertexBuffer() {
    glDeleteBuffers(1, &mID);
}

template class vertexBuffer<float>;
template class vertexBuffer<unsigned int>;
