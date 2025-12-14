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
        
        // Material
        m_Shader->setUniform3f("u_Material.ambient", m_Ambient);
        m_Shader->setUniform3f("u_Material.diffuse", m_Diffuse);
        m_Shader->setUniform3f("u_Material.specular", m_Specular);
        m_Shader->setUniform1f("u_Material.shininess", m_Shininess);
        
        // Light
        m_Shader->setUniform3f("u_Light.position", light.getPosition());
        m_Shader->setUniform3f("u_Light.ambient", light.getAmbient());
        m_Shader->setUniform3f("u_Light.diffuse", light.getDiffuse());
        m_Shader->setUniform3f("u_Light.specular", light.getSpecular());
        
        m_Shader->setUniform3f("u_ViewPos", viewPos);
        // m_Shader->setUniform1i("u_Texture", 0);
    }

    void Material::setAmbient(const glm::vec3 &ambient)
    {
        m_Ambient = ambient;
    }

    void Material::setDiffuse(const glm::vec3 &diffuse)
    {
        m_Diffuse = diffuse;
    }

    void Material::setSpecular(const glm::vec3 &specular)
    {
        m_Specular = specular;
    }

    void Material::setShininess(float shininess)
    {
        m_Shininess = shininess;
    }

    const glm::vec3 &Material::getAmbient() const
    {
        return m_Ambient;
    }

    const glm::vec3 &Material::getDiffuse() const
    {
        return m_Diffuse;
    }

    const glm::vec3 &Material::getSpecular() const
    {
        return m_Specular;
    }

    float Material::getShininess() const
    {
        return m_Shininess;
    }

    bool Material::hasTexture() const
    {
        return m_Texture != nullptr;
    }
} // namespace MykaEngine
