#include "myka_renderer.hpp"

namespace MykaEngine
{
    void Renderer::clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::drawScene(const Scene &scene, const Camera camera) const
    {
        if (scene.getLights().empty())
        {
            return;
        }

        const auto& light = *scene.getLights()[0];

        for (const auto& object : scene.getGameObjects())
        {
            // drawObject(*object, camera, light);
        }
    }

    void Renderer::drawObject(const GameObject &object, const Camera &camera, const Light& light) const
    {
        const auto& transform = object.getTransform();
        const auto& material = object.getMaterial();
        const auto& mesh = object.getMesh();

        glm::mat4 model = transform.getModelMatrix();
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 proj = camera.getProjectionMatrix();

        material->bindShader();
        material->setUniforms(model, view, proj, camera.getPosition(), light);
        // material->bindTexture();
        
        mesh->bind();

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->getIndexCount()), GL_UNSIGNED_INT, 0);

        mesh->unbind();
    }
    

} // namespace MykaEngine
