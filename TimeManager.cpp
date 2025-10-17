#include "TimeManager.h"

void TimeManager::UpdateDeltaTime()
{
	deltaTime = static_cast<float>(glfwGetTime()) - lastFrame;
	lastFrame = static_cast<float>(glfwGetTime());
}

float TimeManager::GetDeltaTime() const
{
	return deltaTime;
}