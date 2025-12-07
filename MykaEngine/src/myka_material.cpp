#include "myka_material.hpp"

namespace MykaEngine
{
    Material::Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture) : m_Shader(shader), m_Texture(texture) {}

    void Material::useShader() const
    {
        m_Shader->use();
    }

    void Material::useTexture() const
    {
        m_Texture->bind(0);
    }

    void Material::useUniforms(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj) const
    {
        glm::mat4 mvp = proj * view * model;

        m_Shader->setUniformMat4f("u_MVP", mvp);
        m_Shader->setUniform3f("u_Color", m_Color);
        m_Shader->setUniform1i("u_Texture", 0);
    }

    void Material::setColor(const glm::vec3 &color)
    {
        m_Color = color;
    }
} // namespace MykaEngine
