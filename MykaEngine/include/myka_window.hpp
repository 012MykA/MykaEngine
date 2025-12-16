#pragma once

#include "myka_logger.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// std
#include <string>
#include <stdexcept>

namespace MykaEngine
{
    class MykaWindow
    {
    public:
        MykaWindow(uint32_t width, uint32_t height, const std::string& title, bool fullscreen);
        ~MykaWindow();

        MykaWindow(const MykaWindow&) = delete;
        MykaWindow& operator=(const MykaWindow&) = delete;

        bool shouldClose() const;

        void pollEvents() const;
        void swapBuffers() const;

        void setWindowTitle(const std::string& title);
    
    public:
        GLFWwindow* getWindow();

    private:
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

        std::string m_Title;
        uint32_t m_Width;
        uint32_t m_Height;

        GLFWmonitor* m_Monitor;
        GLFWwindow* m_Window;
    };
} // namespace MykaEngine
