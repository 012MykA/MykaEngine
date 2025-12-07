#pragma once

#include <GLFW/glfw3.h>

namespace MykaEngine
{
    class Timer
    {
    public:
        Timer() = delete;

        static void onUpdate();
        static float getDeltaTime() { return m_DeltaTime; }

    private:
        inline static float m_DeltaTime = 0;
        inline static float m_LastFrame = static_cast<float>(glfwGetTime());
    };
} // namespace MykaEngine
