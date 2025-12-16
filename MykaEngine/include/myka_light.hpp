#pragma once

#include <glm/glm.hpp>

// std
#include <memory>

namespace MykaEngine
{
    // TODO: separate to diffuse, direct, point
    class Light
    {
    public:
        Light() = default;
        ~Light() = default;

    public:
        void setPosition(const glm::vec3 &position);

        const glm::vec3 &getPosition() const;
        const glm::vec3 &getDirection() const;
        const glm::vec3 &getAmbient() const;
        const glm::vec3 &getDiffuse() const;
        const glm::vec3 &getSpecular() const;

    public:
        glm::vec3 m_Position = glm::vec3(0.0f);
        glm::vec3 m_Direction = glm::vec3(0.0f, -1.0f, 0.0f);

        glm::vec3 m_Ambient = glm::vec3(0.2f);
        glm::vec3 m_Diffuse = glm::vec3(0.8f);
        glm::vec3 m_Specular = glm::vec3(1.0f);

        float constant = 1.0f;
        float linear = 0.09f;
        float quadratic = 0.032f;
    };
} // namespace MykaEngine
