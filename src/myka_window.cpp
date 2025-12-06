#include "myka_window.hpp"

namespace MykaEngine
{
    MykaWindow::MykaWindow(uint32_t width, uint32_t height, const std::string &title) : m_Width(width), m_Height(height), m_Title(title)
    {
        initWindow();
    }

    MykaEngine::MykaWindow::~MykaWindow()
    {
        shutdown();
    }

    bool MykaWindow::shouldClose() const
    {
        return glfwWindowShouldClose(m_Window);
    }

    void MykaWindow::pollEvents() const
    {
        glfwPollEvents();
    }

    void MykaWindow::swapBuffers() const
    {
        glfwSwapBuffers(m_Window);
    }

    GLFWwindow *MykaWindow::getWindow()
    {
        return m_Window;
    }

    void MykaEngine::MykaWindow::initWindow()
    {
        if (!glfwInit())
        {
            throw std::runtime_error("failed to initialize glfw");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
        if (m_Window == nullptr)
        {
            throw std::runtime_error("failed to create glfw window");
        }
        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            throw std::runtime_error("failed to load gl");
        }
        glViewport(0, 0, m_Width, m_Height);
    }

    void MykaEngine::MykaWindow::shutdown()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
} // namespace MykaEngine
