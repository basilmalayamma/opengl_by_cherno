#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_

class indexBuffer {
public:
    indexBuffer(unsigned int size);
    indexBuffer(unsigned int size, unsigned int *data);
    void bind();
    void unBind();
    ~indexBuffer();
    int count();
private:
    unsigned int mID;
    int mIndexCount;
};

#endif
