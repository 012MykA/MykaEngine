#include "Timer.hpp"

namespace MykaEngine
{
    void Timer::onUpdate()
    {
        m_DeltaTime = static_cast<float>(glfwGetTime()) - m_LastFrame;
        m_LastFrame = static_cast<float>(glfwGetTime());
    }
} // namespace MykaEngine
