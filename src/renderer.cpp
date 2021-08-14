#include <renderer.h>

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::clear() {
    glClearColor(0, 0, 0, 0);
}

void Renderer::render(
	std::shared_ptr<vertexArray> va,
	std::shared_ptr<indexBuffer> ib) {
    ib->bind();
    va->bind();
    glDrawElements(GL_TRIANGLES, va->size() * ib->count(), GL_UNSIGNED_INT, nullptr);
}
