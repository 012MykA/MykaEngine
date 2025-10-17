#include "Camera.h"

Camera::Camera(int width, int height, const glm::vec3& position) : m_Width(width), m_Height(height), m_Position(position) {}

void Camera::UpdateMatrices()
{
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);

	m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), (float)m_Width / (float)m_Height, m_Near, m_Far);
}

const glm::mat4& Camera::GetViewMatrix() const { return m_ViewMatrix; }

const glm::mat4& Camera::GetProjectionMatrix() const { return m_ProjectionMatrix; }

void Camera::OnUpdate(GLFWwindow* window, float deltaTime)
{
	Inputs(window, deltaTime);
	UpdateMatrices();
}

void Camera::Inputs(GLFWwindow* window, float deltaTime)
{
	// Keyboard
	float velocity = m_Speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_Position += velocity * m_Front;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_Position += velocity * -glm::normalize(glm::cross(m_Front, m_Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_Position += velocity * -m_Front;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_Position += velocity * glm::normalize(glm::cross(m_Front, m_Up));
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_Position += velocity * m_Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		m_Position += velocity * -m_Up;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		m_Speed = m_DefaultSpeed * 3.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		m_Speed = m_DefaultSpeed;
	}

	// Mouse
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		if (m_FirstClick)
		{
			m_LastX = mouseX;
			m_LastY = mouseY;
			m_FirstClick = false;
		}

		float xoffset = (float)mouseX - (float)m_LastX;
		float yoffset = (float)m_LastY - (float)mouseY;

		m_LastX = mouseX;
		m_LastY = mouseY;

		xoffset *= m_MouseSensitivity;
		yoffset *= m_MouseSensitivity;

		m_Yaw += xoffset;
		m_Pitch += yoffset;

		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_FirstClick = true;
	}
}