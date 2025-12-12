#pragma once

#include "myka_shader.hpp"
#include "myka_texture.hpp"
#include "myka_light.hpp"

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
        void bindShader() const;
        void bindTexture() const;
        void setUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &proj, const Light& light, bool isLight) const;

    public:
        void setColor(const glm::vec3 &color);

        const glm::vec3& getColor() const;

    public: // TODO: private
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<Texture> m_Texture;

        glm::vec3 m_Color = glm::vec3(1.0f);
        float m_Shininess = 32.0f;
    };
} // namespace MykaEngine
