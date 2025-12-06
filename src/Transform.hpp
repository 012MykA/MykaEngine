#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace MykaEngine
{
    class Transform
    {
    public:
        Transform();

    public:
        void setPosition(const glm::vec3& position);
        void setRotation(const glm::vec3& rotation);
        void setScale(const glm::vec3& scale);

        const glm::mat4& getModelMatrix() const;

    private:
        void updateModelMatrix();

        glm::vec3 m_Position{0.0f};
        glm::vec3 m_Rotation{0.0f};
        glm::vec3 m_Scale{1.0f};

        glm::mat4 m_ModelMatrix{1.0f};
    };
} // namespace MykaEngine
