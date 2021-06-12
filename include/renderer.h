#ifndef RENDERER_H
#define RENDERER_H

#include <vertexArray.h>
#include <indexBuffer.h>

class Renderer {
public:
    Renderer();
    ~Renderer();
    void render(vertexArray &va, indexBuffer &ib);
    void clear();
private:

};

#endif //RENDERER_H
