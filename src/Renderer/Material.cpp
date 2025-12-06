#include "Material.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    void Material::useUniforms() const
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 proj = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
        glm::mat4 modelViewProj = proj * view * model;

        m_Shader->setUniformMat4f("u_MVP", modelViewProj);
        m_Shader->setUniform4f("u_Color", m_Color);
        m_Shader->setUniform1i("u_Texture", 0);
    }

    void Material::setColor(const glm::vec4 &color)
    {
        m_Color = color;
    }
} // namespace MykaEngine
