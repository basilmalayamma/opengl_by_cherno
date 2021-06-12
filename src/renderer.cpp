#include <renderer.h>

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::clear() {
    glClearColor(0, 0, 0, 0);
}

void Renderer::render(vertexArray &va, indexBuffer &ib) {
    ib.bind();
    va.bind();
    //glDrawElements(GL_TRIANGLES, va.size() * ib.count(), GL_UNSIGNED_INT, nullptr);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
