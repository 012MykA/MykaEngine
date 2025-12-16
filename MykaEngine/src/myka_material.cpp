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

    void Material::unbindTextures()
    {
        for (const auto& [name, texture] : m_Textures)
        {
            if (texture != nullptr)
            {
                texture->unbind();
            }
        }
    }

    void Material::setUniform(const std::string &name, const UniformValue &value)
    {
        m_Uniforms[name] = value;
    }

    void Material::applyUnuiforms() const
    {
        if (!m_Shader)
        {
            Logger::logError("cannot apply uniforms to a shader. Add a shader first");
            return;
        }

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

        for (const auto& [name, texture] : m_Textures)
        {
            if (texture != nullptr)
            {
                GLuint slot = m_TextureSlots.at(name);
                
                texture->bind(slot);
                m_Shader->setUniformInt(name, slot);
            }
            else
            {
                Logger::logWarning("attempt to bind texture: " + name + " is nullptr");
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
        Logger::logError("failed to find uniform: '" + name + "' in Material::getUniform method");
    }
} // namespace MykaEngine
