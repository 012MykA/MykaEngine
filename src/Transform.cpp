#include "Transform.hpp"

namespace MykaEngine
{
    Transform::Transform()
    {
        updateModelMatrix();
    }

    void Transform::updateModelMatrix()
    {
        glm::mat4 model{1.0f};

        model = glm::scale(model, m_Scale);

        model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        model = glm::translate(model, m_Position);

        m_ModelMatrix = model;
    }
} // namespace MykaEngine
