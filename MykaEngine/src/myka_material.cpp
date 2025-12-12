#include "myka_material.hpp"

namespace MykaEngine
{
    Material::Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture) : m_Shader(shader), m_Texture(texture) {}

    void Material::bindShader() const
    {
        m_Shader->use();
    }

    void Material::bindTexture() const
    {
        m_Texture->bind(0);
    }

    void Material::setUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &proj, const glm::vec3 &viewPos, const Light &light) const
    {
        glm::mat4 mvp = proj * view * model;

        m_Shader->setUniformMat4f("u_MVP", mvp);
        m_Shader->setUniformMat4f("u_Model", model);
        if (hasTexture())
        {
            m_Shader->setUniform1i("u_Texture", 0);
        }
        m_Shader->setUniform3f("u_LightColor", light.getColor());
        m_Shader->setUniform3f("u_ObjectColor", m_Color);
        m_Shader->setUniform3f("u_LightPos", light.getPosition());
        m_Shader->setUniform3f("u_ViewPos", viewPos);
    }

    void Material::setColor(const glm::vec3 &color)
    {
        m_Color = color;
    }

    const glm::vec3 &Material::getColor() const
    {
        return m_Color;
    }

    bool Material::hasTexture() const
    {
        return m_Texture != nullptr;
    }
} // namespace MykaEngine
