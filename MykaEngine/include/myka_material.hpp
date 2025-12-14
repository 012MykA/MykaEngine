#pragma once

#include "myka_shader.hpp"
#include "myka_texture.hpp"
#include "myka_light.hpp"

#include <glm/glm.hpp>

// std
#include <memory>
#include <unordered_map>
#include <variant>
#include <any>
#include <stdexcept>

namespace MykaEngine
{
    using UniformValue = std::variant<
        bool, int, float,
        glm::vec2, glm::vec3, glm::vec4,
        glm::mat3, glm::mat4
    >;

    class Material
    {
    public:
        Material() = default;
        Material(std::shared_ptr<Shader> shader);

        void setShader(std::shared_ptr<Shader> shader);
        std::shared_ptr<Shader> getShader() const;

        void setTexture(const std::string& name, std::shared_ptr<Texture> texture);
        void setTextureSlot(const std::string& name, GLuint slot);

        void setUniform(const std::string& name, const UniformValue& value);
        void applyUnuiforms() const;

        template<typename T>
        T getUniform(const std::string& name) const;

    private:
        std::shared_ptr<Shader> m_Shader;
        std::unordered_map<std::string, UniformValue> m_Uniforms;

        std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
        std::unordered_map<std::string, GLuint> m_TextureSlots;
        GLuint m_NextTextureSlot = 0;

    // public:
    //     void bindShader() const;
    //     void bindTexture() const;

    //     void setUniforms(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &proj, const glm::vec3 &viewPos, const Light &light) const;

    // public:
    //     bool hasTexture() const;

    //     void setAmbient(const glm::vec3 &ambient);
    //     void setDiffuse(const glm::vec3 &diffuse);
    //     void setSpecular(const glm::vec3 &specular);
    //     void setShininess(float shininess);

    //     const glm::vec3 &getAmbient() const;
    //     const glm::vec3 &getDiffuse() const;
    //     const glm::vec3 &getSpecular() const;
    //     float getShininess() const;

    // public: // TODO: private
    //     std::shared_ptr<Shader> m_Shader;
    //     std::shared_ptr<Texture> m_Texture;

    //     glm::vec3 m_Ambient{0.19225f};
    //     glm::vec3 m_Diffuse{0.50754f};
    //     glm::vec3 m_Specular{0.508273f};
    //     float m_Shininess = 0.4f;
    };
} // namespace MykaEngine
