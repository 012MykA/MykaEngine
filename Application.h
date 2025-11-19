#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Camera.h"
#include "Scene.h"
#include "TimeManager.h"
#include "ImGuiManager.h"
#include "MeshLibrary.h"
#include "Deps.h"

class Application
{
public:
	Application();
	~Application();

	void Run();

private:
	void OnUpdate();
	void PollEvents(float deltaTime);
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* window;
	ImGuiManager imguiManager;
	TimeManager timeManager;

	PhysicsEngine physicsEngine;
	Camera camera;
	Renderer renderer;

	Scene scene;
};