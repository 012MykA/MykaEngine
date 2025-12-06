#include "Renderer.hpp"

namespace MykaEngine
{
    void Renderer::clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::draw(const Mesh &mesh, const Material &material) const
    {
        material.useShader();
        material.useUniforms();
        material.useTexture();
        
        mesh.bind();

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.getIndexCount()), GL_UNSIGNED_INT, 0);

        mesh.unbind();
    }
} // namespace MykaEngine
