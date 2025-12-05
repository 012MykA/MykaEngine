#include "Renderer.hpp"

namespace MykaEngine
{
    void Renderer::clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void MykaEngine::Renderer::draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const
    {
        shader.use();

        va.bind();
        ib.bind();

        glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, 0);

        // not necessary
        // va.unbind();
        // ib.unbind();
    }
} // namespace MykaEngine
