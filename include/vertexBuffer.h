#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

template<typename T>
class vertexBuffer {
public:
    vertexBuffer(unsigned int target, unsigned int size, T *data);
    bool bindBuffer(GLenum target);
    bool unBindBuffer(GLenum target);
    ~vertexBuffer();
private:
    unsigned int mID;
};

#endif
