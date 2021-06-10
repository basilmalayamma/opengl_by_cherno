#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_

class indexBuffer {
public:
    indexBuffer(unsigned int size, unsigned int *data);
    void bind();
    void unBind();
    ~indexBuffer();
private:
    unsigned int mID;
};

#endif
