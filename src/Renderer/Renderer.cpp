#include "Renderer.hpp"

namespace MykaEngine
{
    void Renderer::clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::draw(const GameObject &object, const Camera &camera) const
    {
        const auto& transform = object.getTransform();
        const auto& material = object.getMaterial();
        const auto& mesh = object.getMesh();

        glm::mat4 model = transform.getModelMatrix();
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 proj = camera.getProjectionMatrix();

        material->useShader();
        material->useUniforms(model, view, proj);
        material->useTexture();
        
        mesh->bind();

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->getIndexCount()), GL_UNSIGNED_INT, 0);

        mesh->unbind();
    }
} // namespace MykaEngine
