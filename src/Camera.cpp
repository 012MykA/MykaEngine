#include "Camera.hpp"
#include <iostream> // TODO: remove

namespace MykaEngine
{
    Camera::Camera(float width, float height, GLFWwindow *window)
        : m_Width(width), m_Height(height), m_Window(window) {}

    void Camera::onUpdate()
    {
        updateViewMatrix();
        updateProjectionMatrix();
    }

    void Camera::handleInputs()
    {
        float deltaTime = Timer::getDeltaTime();
        
        if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
        {
            m_Position += m_Velocity * deltaTime * m_Front;
        }
        if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
        {
            m_Position += m_Velocity * deltaTime * -glm::normalize(glm::cross(m_Front, m_Up));
        }
        if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
        {
            m_Position += m_Velocity * deltaTime * -m_Front;
        }
        if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
        {
            m_Position += m_Velocity * deltaTime * glm::normalize(glm::cross(m_Front, m_Up));
        }

        if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            m_Position += m_Velocity * deltaTime * m_Up;
        }
        if (glfwGetKey(m_Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            m_Position += m_Velocity * deltaTime * -m_Up;
        }
        // TODO: remove
        std::cout << m_Position.x << "\t" << m_Position.y << "\t" << m_Position.z << std::endl;

        // if (glfwGetKey(m_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        // {
        //     m_Speed = m_DefaultSpeed * 3.0f;
        // }
        // if (glfwGetKey(m_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        // {
        //     m_Speed = m_DefaultSpeed;
        // }
    }

    void Camera::updateViewMatrix()
    {
        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }

    void Camera::updateProjectionMatrix()
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_Width / m_Height, m_Near, m_Far);
    }

} // namespace MykaEngine
