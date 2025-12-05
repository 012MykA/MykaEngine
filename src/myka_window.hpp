#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// std
#include <iostream>
#include <string>
#include <stdexcept>

namespace MykaEngine
{
    class MykaWindow
    {
    public:
        MykaWindow(uint32_t width, uint32_t height, const std::string& title);
        ~MykaWindow();

        MykaWindow(const MykaWindow&) = delete;
        MykaWindow& operator=(const MykaWindow&) = delete;

        bool shouldClose();
        void onUpdate();

    private:
        void initWindow();
        void shutdown();

        std::string m_Title;
        uint32_t m_Width;
        uint32_t m_Height;

        GLFWwindow* window;
    };
} // namespace MykaEngine
