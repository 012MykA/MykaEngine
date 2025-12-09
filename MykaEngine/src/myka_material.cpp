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

    void Material::useUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &proj,
                               const glm::vec3 &viewPos, const Light &light) const
    {
        m_Shader->use();

        glm::mat4 mvp = proj * view * model;
        glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));

        m_Shader->setUniformMat4f("u_MVP", mvp);
        m_Shader->setUniformMat4f("u_Model", model);
        m_Shader->setUniformMat4f("u_NormalMatrix", glm::mat4(normalMatrix));
        m_Shader->setUniform3f("u_ViewPos", viewPos);

        m_Shader->setUniform3f("u_Material.color", m_Color);
        m_Shader->setUniform1f("u_Material.shininess", m_Shininess);

        m_Shader->setUniform3f("u_Light.position", light.getPosition());
        m_Shader->setUniform3f("u_Light.ambient", light.getAmbient());
        m_Shader->setUniform3f("u_Light.diffuse", light.getDiffuse());
        m_Shader->setUniform3f("u_Light.specular", light.getSpecular());

        m_Shader->setUniform1i("u_Texture", 0);
    }

    void Material::setColor(const glm::vec3 &color)
    {
        m_Color = color;
    }
} // namespace MykaEngine
