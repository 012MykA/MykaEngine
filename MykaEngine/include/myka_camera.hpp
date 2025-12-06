#pragma once

#include <algorithm>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "myka_timer.hpp"

namespace MykaEngine
{
    class Camera
    {
    public:
        Camera(float width, float height, GLFWwindow *window);

        void onUpdate();

        void handleInputs();

    public:
        const glm::mat4 &getViewMatrix() const;
        const glm::mat4 &getProjectionMatrix() const;

    private:
        void updateViewMatrix();
        void updateProjectionMatrix();

        glm::vec3 m_Position{0.0f, 0.0f, 0.0f};
        glm::vec3 m_Front{0.0, 0.0f, -1.0f};
        glm::vec3 m_Up{0.0f, 1.0f, 0.0f};
        float m_Yaw = -90.0f;
        float m_Pitch = 0.0f;

        float m_FOV = 70;
        float m_Near = 0.01f;
        float m_Far = 1000.0f;

        float m_Velocity = 2.0f;

        float m_Width;
        float m_Height;
        GLFWwindow *m_Window;

        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;

        bool m_FirstClick = true;
        float m_MouseSensitivity = 0.05f;
        double m_LastX;
        double m_LastY;
    };
} // namespace MykaEngine
