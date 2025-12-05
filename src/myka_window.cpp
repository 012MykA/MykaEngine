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

    bool MykaWindow::shouldClose()
    {
        return glfwWindowShouldClose(window);
    }

    void MykaWindow::onUpdate()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
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

        window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
        if (window == nullptr)
        {
            throw std::runtime_error("failed to create glfw window");
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            throw std::runtime_error("failed to load gl");
        }
    }

    void MykaEngine::MykaWindow::shutdown()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
} // namespace MykaEngine
