#include "Transform.hpp"

namespace MykaEngine
{
    Transform::Transform()
    {
        updateModelMatrix();
    }

    // Set
    void Transform::setPosition(const glm::vec3 &position)
    {
        m_Position = position;
        updateModelMatrix();
    }

    void Transform::setRotation(const glm::vec3 &rotation)
    {
        m_Rotation = rotation;
        updateModelMatrix();
    }

    void Transform::setScale(const glm::vec3 &scale)
    {
        m_Scale = scale;
        updateModelMatrix();
    }

    const glm::mat4 &Transform::getModelMatrix() const
    {
        return m_ModelMatrix;
    }

    void Transform::updateModelMatrix()
    {
        glm::mat4 model{1.0f};

        model = glm::translate(model, m_Position);
        
        model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        
        model = glm::scale(model, m_Scale);

        m_ModelMatrix = model;
    }
} // namespace MykaEngine
