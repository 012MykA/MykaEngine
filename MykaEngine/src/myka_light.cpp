#include "myka_light.hpp"

namespace MykaEngine
{
    Light::Light(const glm::vec3 &position,
                 const glm::vec3 &ambient,
                 const glm::vec3 &diffuse,
                 const glm::vec3 &specular)
        : m_Position(position), m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular) {}

    void Light::setPosition(const glm::vec3 &position)
    {
        m_Position = position;
    }

    const glm::vec3 &Light::getPosition() const
    {
        return m_Position;
    }

    const glm::vec3 &Light::getAmbient() const
    {
        return m_Ambient;
    }

    const glm::vec3 &Light::getDiffuse() const
    {
        return m_Diffuse;
    }

    const glm::vec3 &Light::getSpecular() const
    {
        return m_Specular;
    }

} // namespace MykaEngine
