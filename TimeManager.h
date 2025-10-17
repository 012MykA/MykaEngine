#pragma once

#include <GLFW/glfw3.h>

class TimeManager
{
public:
	void UpdateDeltaTime();

	float GetDeltaTime() const;

private:
	float deltaTime;
	float lastFrame;
};