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

    private:
        void updateModelMatrix();

        glm::vec3 m_Position{0.0f};
        glm::vec3 m_Rotation{0.0f};
        glm::vec3 m_Scale{1.0f};

        glm::mat4 m_ModelMatrix{1.0f};
    };
} // namespace MykaEngine
