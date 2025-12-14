#pragma once

#include <glm/glm.hpp>

// std
#include <memory>

namespace MykaEngine
{
    class Light
    {
    public:
        Light(const glm::vec3 &position,
              const glm::vec3 &ambient,
              const glm::vec3 &diffuse,
              const glm::vec3 &specular
        );

    public:
        void setPosition(const glm::vec3 &position);

        const glm::vec3 &getPosition() const;
        const glm::vec3 &getAmbient() const;
        const glm::vec3 &getDiffuse() const;
        const glm::vec3 &getSpecular() const;

    private:
        glm::vec3 m_Position;
        glm::vec3 m_Ambient;
        glm::vec3 m_Diffuse;
        glm::vec3 m_Specular;
    };
} // namespace MykaEngine
