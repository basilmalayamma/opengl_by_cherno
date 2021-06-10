#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

class vertexBuffer {
public:
    vertexBuffer(unsigned int size, float *data);
    void bind();
    void unBind();
    ~vertexBuffer();
private:
    unsigned int mID;
};

#endif
