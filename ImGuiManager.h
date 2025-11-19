#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Camera.h"
#include "Scene.h"
#include "MeshLibrary.h"

class ImGuiManager
{
public:
	void Initialize(GLFWwindow* window);

	void NewFrame();

	void Render(Scene& scene, Camera& camera);
	void PollEvents();

	void Shutdown();

private:
	bool show_main_window = true;

	bool window_auto_resize = false;
	bool vSyncEnabled = true;
};
