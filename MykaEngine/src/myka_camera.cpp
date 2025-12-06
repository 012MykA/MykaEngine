#include "myka_camera.hpp"

namespace MykaEngine
{
    Camera::Camera(float width, float height, GLFWwindow *window)
        : m_Width(width), m_Height(height), m_Window(window)
    {
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        updateViewMatrix();
        updateProjectionMatrix();
    }

    const glm::mat4 &Camera::getViewMatrix() const
    {
        return m_ViewMatrix;
    }

    const glm::mat4 &Camera::getProjectionMatrix() const
    {
        return m_ProjectionMatrix;
    }

    void Camera::updateProjectionMatrix()
    {
        float aspectRatio = m_Width / m_Height;
        m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), aspectRatio, m_Near, m_Far);
    }

    void Camera::updateViewMatrix()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front = glm::normalize(front);

        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }

    void Camera::handleInputs()
    {
        if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            m_FirstClick = true;
            return;
        }

        if (glfwGetInputMode(m_Window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
        {
            if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            return;
        }

        float velocity = m_Velocity * Timer::getDeltaTime();
        glm::vec3 right = glm::normalize(glm::cross(m_Front, m_Up));

        if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
            m_Position += m_Front * velocity;
        if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
            m_Position -= m_Front * velocity;
        if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
            m_Position -= right * velocity;
        if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
            m_Position += right * velocity;

        if (glfwGetKey(m_Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            m_Position -= m_Up * velocity;
        if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
            m_Position += m_Up * velocity;

        double xpos, ypos;
        glfwGetCursorPos(m_Window, &xpos, &ypos);

        if (m_FirstClick)
        {
            m_LastX = xpos;
            m_LastY = ypos;
            m_FirstClick = false;
        }

        float xoffset = (float)(xpos - m_LastX) * m_MouseSensitivity;
        float yoffset = (float)(m_LastY - ypos) * m_MouseSensitivity;

        m_LastX = xpos;
        m_LastY = ypos;

        m_Yaw += xoffset;
        m_Pitch += yoffset;

        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;
        
        glfwSetCursorPos(m_Window, m_Width / 2.0, m_Height / 2.0);
        m_LastX = m_Width / 2.0;
        m_LastY = m_Height / 2.0;
    }

    void Camera::onUpdate()
    {
        handleInputs();
        updateViewMatrix();
        updateProjectionMatrix();
    }
} // namespace MykaEngine