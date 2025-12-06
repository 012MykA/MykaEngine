#pragma once

#include "myka_shader.hpp"
#include "myka_texture.hpp"

#include <glm/glm.hpp>

// std
#include <memory>

namespace MykaEngine
{
    class Material
    {
    public:
        Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);

    public:
        void useShader() const;
        void useTexture() const;
        void useUniforms(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj) const;

        void setColor(const glm::vec4& color);

    private:
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<Texture> m_Texture;

        float m_Ambient = 0.2f;    // Object color in dark
        glm::vec4 m_Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        float m_Specular = 0.5f;   // Smoothness
    };
} // namespace MykaEngine
