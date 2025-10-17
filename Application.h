#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Camera.h"
#include "Scene.h"
#include "TimeManager.h"
#include "ImGuiManager.h"

class Application
{
public:
	Application();
	~Application();

	void Run();

private:
	void OnUpdate();
	void PollEvents(float deltaTime);

	GLFWwindow* window;
	ImGuiManager imguiManager;
	TimeManager timeManager;

	Camera camera;
	Renderer renderer;

	Scene scene;
};