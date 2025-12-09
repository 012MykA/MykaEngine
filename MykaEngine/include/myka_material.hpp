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
        void useShader() const;
        void useTexture() const;
        void useUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &proj,
                         const glm::vec3 &viewPos, const Light &light) const;

        void setColor(const glm::vec3 &color);

    private:
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<Texture> m_Texture;

        glm::vec3 m_Color = glm::vec3(1.0f);
        float m_Shininess = 32.0f;
    };
} // namespace MykaEngine
