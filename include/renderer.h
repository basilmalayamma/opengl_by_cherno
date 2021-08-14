#ifndef RENDERER_H
#define RENDERER_H

#include <vertexArray.h>
#include <indexBuffer.h>
#include <memory>

class Renderer {
public:
    Renderer();
    ~Renderer();
    void render(
	std::shared_ptr<vertexArray> va,
	std::shared_ptr<indexBuffer> ib);
    void clear();
private:

};

#endif //RENDERER_H
