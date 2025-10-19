#include "ImGuiManager.h"

void ImGuiManager::Initialize(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiManager::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::Render(Scene& scene, Camera& camera)
{
	ImGui::ShowDemoWindow();

	if (ImGui::Begin("MykaEngine"))
	{
		if (ImGui::BeginTabBar("MainTabBar"))
		{
			if (ImGui::BeginTabItem("Scene"))
			{
				if (ImGui::CollapsingHeader("Objects"))
				{
					size_t objectIndex = 0;
					for (auto& object : scene.GetObjects())
					{
						std::string objectName = object->GetName() + " (" + std::to_string(objectIndex) + ")";
						if (ImGui::TreeNode(objectName.c_str()))
						{
							{
								ImGui::SeparatorText("Kinematics");
								float* position[3] = { &object->physics.position.x, &object->physics.position.y, &object->physics.position.z };
								ImGui::DragFloat3("Position", *position, 0.1f); // TODO: add limits

								ImGui::Separator();

								float* velocity[3] = { &object->physics.velocity.x, &object->physics.velocity.y, &object->physics.velocity.z };
								ImGui::DragFloat3("Velocity", *velocity, 0.1f);

								ImGui::Separator();

								float* acceleration[3] = { &object->physics.acceleration.x, &object->physics.acceleration.y, &object->physics.acceleration.z };
								ImGui::DragFloat3("Acceleration", *acceleration, 0.1f);
							}

							{
								ImGui::SeparatorText("Properties");
								ImGui::DragFloat("Mass", &object->physics.mass, 0.1f);

							}



							ImGui::TreePop();
						}

						objectIndex++;
					}
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Camera"))
			{
				ImGui::SeparatorText("Properties");
				ImGui::DragFloat("FOV", &camera.m_FOV, 1.0f, 50.0f, 110.0f, "%.0f");
				ImGui::DragFloat("Render distance", &camera.m_Far, 1.0f, 1.0f, 1000.0f, "%.0f");

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}


	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}