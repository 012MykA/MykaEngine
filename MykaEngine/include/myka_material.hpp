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
        void unbindTextures();

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
    };
} // namespace MykaEngine
