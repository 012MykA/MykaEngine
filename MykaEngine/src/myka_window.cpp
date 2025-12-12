#include "myka_window.hpp"

namespace MykaEngine
{
    MykaWindow::MykaWindow(uint32_t width, uint32_t height, const std::string &title, bool fullscreen) : m_Width(width), m_Height(height), m_Title(title)
    {
        if (!glfwInit())
        {
            throw std::runtime_error("failed to initialize glfw");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Monitor = glfwGetPrimaryMonitor();

        const GLFWvidmode *mode = glfwGetVideoMode(m_Monitor);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        m_Window = glfwCreateWindow(mode->width, mode->height, m_Title.c_str(), fullscreen ? m_Monitor : NULL, NULL);

        if (m_Window == nullptr)
        {
            throw std::runtime_error("failed to create glfw window");
        }
        glfwMakeContextCurrent(m_Window);
        glfwSetFramebufferSizeCallback(m_Window, framebufferSizeCallback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            throw std::runtime_error("failed to load gl");
        }
        glViewport(0, 0, m_Width, m_Height);
    }

    MykaEngine::MykaWindow::~MykaWindow()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    bool MykaWindow::shouldClose() const
    {
        return glfwWindowShouldClose(m_Window);
    }

    void MykaWindow::pollEvents() const
    {
        glfwPollEvents();

        if (glfwGetKey(m_Window, GLFW_KEY_T) == GLFW_PRESS)
        {
            glEnable(GL_POLYGON_SMOOTH);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        if (glfwGetKey(m_Window, GLFW_KEY_T) == GLFW_RELEASE)
        {
            glDisable(GL_POLYGON_SMOOTH);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
        }
    }

    void MykaWindow::swapBuffers() const
    {
        glfwSwapBuffers(m_Window);
    }

    void MykaWindow::setWindowTitle(const std::string &title)
    {
        m_Title = title;
        glfwSetWindowTitle(m_Window, m_Title.c_str());
    }

    GLFWwindow *MykaWindow::getWindow()
    {
        return m_Window;
    }

    void MykaWindow::framebufferSizeCallback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
} // namespace MykaEngine
