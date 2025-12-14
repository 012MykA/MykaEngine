#include "myka_material.hpp"

namespace MykaEngine
{
    Material::Material(std::shared_ptr<Shader> shader) : m_Shader(shader) {}

    void Material::setShader(std::shared_ptr<Shader> shader)
    {
        m_Shader = shader;
        m_Uniforms.clear();
    }

    std::shared_ptr<Shader> Material::getShader() const
    {
        return m_Shader;
    }

    void Material::setTexture(const std::string &name, std::shared_ptr<Texture> texture)
    {
        m_Textures[name] = texture;

        if (m_TextureSlots.find(name) == m_TextureSlots.end())
        {
            m_TextureSlots[name] = m_NextTextureSlot++;
        }
    }

    void Material::setTextureSlot(const std::string &name, GLuint slot)
    {
        m_TextureSlots[name] = slot;
    }

    void Material::setUniform(const std::string &name, const UniformValue &value)
    {
        m_Uniforms[name] = value;
    }

    void Material::applyUnuiforms() const
    {
        if (!m_Shader)
            return;

        m_Shader->use();

        for (const auto &[name, value] : m_Uniforms)
        {
            std::visit(
                [this, &name](auto &&arg)
                {
                    using T = std::decay_t<decltype(arg)>;

                    if constexpr (std::is_same_v<T, bool>)
                    {
                        m_Shader->setUniformBool(name, arg);
                    }
                    else if constexpr (std::is_same_v<T, int>)
                    {
                        m_Shader->setUniformInt(name, arg);
                    }
                    else if constexpr (std::is_same_v<T, float>)
                    {
                        m_Shader->setUniformFloat(name, arg);
                    }
                    // Vector
                    else if constexpr (std::is_same_v<T, glm::vec2>)
                    {
                        m_Shader->setUniformVec2(name, arg);
                    }
                    else if constexpr (std::is_same_v<T, glm::vec3>)
                    {
                        m_Shader->setUniformVec3(name, arg);
                    }
                    else if constexpr (std::is_same_v<T, glm::vec4>)
                    {
                        m_Shader->setUniformVec4(name, arg);
                    }
                    // Matrix
                    else if constexpr (std::is_same_v<T, glm::mat3>)
                    {
                        m_Shader->setUniformMat3(name, arg);
                    }
                    else if constexpr (std::is_same_v<T, glm::mat4>)
                    {
                        m_Shader->setUniformMat4(name, arg);
                    }
                },
                value);
        }

        for (const auto& [name, texture] :m_Textures)
        {
            if (texture != nullptr)
            {
                GLuint slot = m_TextureSlots.at(name);
                
                texture->bind(slot);
                m_Shader->setUniformInt(name, slot);
            }
        }
    }

    template <typename T>
    T Material::getUniform(const std::string &name) const
    {
        auto it = m_Uniforms.find(name);
        if (it != m_Uniforms.end())
        {
            return std::get<T>(it->second);
        }
        throw std::runtime_error("failed to find uniform: " + name);
    }

    // void Material::bindShader() const
    // {
    //     m_Shader->use();
    // }

    // void Material::bindTexture() const
    // {
    //     m_Texture->bind(0);
    // }

    // void Material::setUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &proj, const glm::vec3 &viewPos, const Light &light) const
    // {
    //     glm::mat4 mvp = proj * view * model;

    //     m_Shader->setUniformMat4("u_MVP", mvp);
    //     m_Shader->setUniformMat4("u_Model", model);

    //     // Material
    //     m_Shader->setUniformVec3("u_Material.ambient", m_Ambient);
    //     m_Shader->setUniformVec3("u_Material.diffuse", m_Diffuse);
    //     m_Shader->setUniformVec3("u_Material.specular", m_Specular);
    //     m_Shader->setUniformFloat("u_Material.shininess", m_Shininess);

    //     // Light
    //     m_Shader->setUniformVec3("u_Light.position", light.getPosition());
    //     m_Shader->setUniformVec3("u_Light.ambient",light .getAmbient());
    //     m_Shader->setUniformVec3("u_Light.diffuse", light.getDiffuse());
    //     m_Shader->setUniformVec3("u_Light.specular", light.getSpecular());

    //     m_Shader->setUniformVec3("u_ViewPos", viewPos);
    //     // m_Shader->setUniform1i("u_Texture", 0);
    // }

    // void Material::setAmbient(const glm::vec3 &ambient)
    // {
    //     m_Ambient = ambient;
    // }

    // void Material::setDiffuse(const glm::vec3 &diffuse)
    // {
    //     m_Diffuse = diffuse;
    // }

    // void Material::setSpecular(const glm::vec3 &specular)
    // {
    //     m_Specular = specular;
    // }

    // void Material::setShininess(float shininess)
    // {
    //     m_Shininess = shininess;
    // }

    // const glm::vec3 &Material::getAmbient() const
    // {
    //     return m_Ambient;
    // }

    // const glm::vec3 &Material::getDiffuse() const
    // {
    //     return m_Diffuse;
    // }

    // const glm::vec3 &Material::getSpecular() const
    // {
    //     return m_Specular;
    // }

    // float Material::getShininess() const
    // {
    //     return m_Shininess;
    // }

    // bool Material::hasTexture() const
    // {
    //     return m_Texture != nullptr;
    // }
} // namespace MykaEngine
