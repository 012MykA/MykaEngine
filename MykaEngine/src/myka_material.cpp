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

    void Material::setUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &proj, const Light& light, bool isLight) const
    {
        m_Shader->use();

        glm::mat4 mvp = proj * view * model;

        m_Shader->setUniformMat4f("u_MVP", mvp);
        if (!isLight)
        {
            m_Shader->setUniform1i("u_Texture", 0);
        }
        m_Shader->setUniform3f("u_LightColor", light.getColor());
    }

    void Material::setColor(const glm::vec3 &color)
    {
        m_Color = color;
    }

    const glm::vec3 &Material::getColor() const
    {
        return m_Color;
    }
} // namespace MykaEngine
