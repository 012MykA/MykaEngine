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

        void setUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &proj, const glm::vec3 &viewPos, const Light &light) const;

    public:
        bool hasTexture() const;

        void setAmbient(const glm::vec3 &ambient);
        void setDiffuse(const glm::vec3 &diffuse);
        void setSpecular(const glm::vec3 &specular);
        void setShininess(float shininess);

        const glm::vec3 &getAmbient() const;
        const glm::vec3 &getDiffuse() const;
        const glm::vec3 &getSpecular() const;
        float getShininess() const;

    public: // TODO: private
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<Texture> m_Texture;

        glm::vec3 m_Ambient{0.19225f};
        glm::vec3 m_Diffuse{0.50754f};
        glm::vec3 m_Specular{0.508273f};
        float m_Shininess = 0.4f;
    };
} // namespace MykaEngine
