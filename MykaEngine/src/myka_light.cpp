#include "myka_light.hpp"

namespace MykaEngine
{
    void Light::setPosition(const glm::vec3 &position)
    {
        m_Position = position;
    }

    const glm::vec3 &Light::getPosition() const
    {
        return m_Position;
    }

    const glm::vec3 &Light::getDirection() const
    {
        return m_Direction;
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
