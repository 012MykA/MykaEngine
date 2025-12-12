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
        Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture = nullptr);

    public:
        void bindShader() const;
        void bindTexture() const;
        virtual void setUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &proj, const glm::vec3 &viewPos, const Light &light) const;

    public:
        void setColor(const glm::vec3 &color);

        const glm::vec3 &getColor() const;
        bool hasTexture() const;

    public: // TODO: private
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<Texture> m_Texture;

        glm::vec3 m_Ambient{0.19225f};
        glm::vec3 m_Diffuse{0.50754f};
        glm::vec3 m_Specular{0.508273f};
        float m_Shininess = 0.4f;
        glm::vec3 m_Color{1.0f};
    };
} // namespace MykaEngine
