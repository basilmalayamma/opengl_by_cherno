#include <renderer.h>

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::clear(float r, float g, float b) {
    glClearColor(r, g, b, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(
	std::shared_ptr<vertexArray> va,
	std::shared_ptr<indexBuffer> ib) {
    ib->bind();
    va->bind();
    glDrawElements(GL_TRIANGLES, va->size() * ib->count(), GL_UNSIGNED_INT, nullptr);
}
