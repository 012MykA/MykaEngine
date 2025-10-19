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
	//ImGui::ShowDemoWindow();

	if (show_main_window)
	{
		if (ImGui::Begin("MykaEngine"))
		{
			if (ImGui::BeginTabBar("MainTabBar"))
			{
				if (ImGui::BeginTabItem("Scene"))
				{
					// Properties
					ImGui::SeparatorText("Properties");
					ImGui::Checkbox("Gravity", &scene.gravityEnabled);
					float* gravity[3] = { &scene.gravity.x, &scene.gravity.y, &scene.gravity.z };
					ImGui::DragFloat3("Gravity vector", *gravity, 0.1f);

					
					// Add new object
					ImGui::SeparatorText("Add new Object");
					std::vector<std::string> shapes = { "Cube", "Sphere", "Plane" };
					static int current_shape = 0;
					const char* preview_value = shapes[current_shape].c_str();
					if (ImGui::BeginCombo("Shape", preview_value))
					{
						for (int n = 0; n < shapes.size(); n++)
						{
							bool is_selected = (current_shape == n);
							if (ImGui::Selectable(shapes[n].c_str(), is_selected))
								current_shape = n;
							if (is_selected)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Objects"))
				{
					ImGui::SeparatorText("Objects");

					size_t objectIndex = 0;
					for (auto& object : scene.GetObjects())
					{
						std::string objectName = object->GetName() + "##" + std::to_string(objectIndex);
						if (ImGui::TreeNode(objectName.c_str()))
						{
							// Properties
							ImGui::SeparatorText("Properties");
							ImGui::DragFloat("Mass", &object->physics.mass, 0.1f, 0.1f, 1000000.0f);
							if (ImGui::IsItemHovered())
							{
								ImGui::BeginTooltip();
								ImGui::Text("Affects on acceleration: F = ma => a = F / m");
								ImGui::EndTooltip();
							}

							// Position
							ImGui::SeparatorText("Kinematics");
							float* position[3] = { &object->physics.position.x, &object->physics.position.y, &object->physics.position.z };
							ImGui::DragFloat3("Position", *position, 0.1f); // TODO: add limits
							ImGui::Separator();

							// Velocity
							float* velocity[3] = { &object->physics.velocity.x, &object->physics.velocity.y, &object->physics.velocity.z };
							ImGui::DragFloat3("Velocity", *velocity, 0.1f);
							if (ImGui::IsItemHovered())
							{
								ImGui::BeginTooltip();
								ImGui::Text("Affects on position: x = x0 + vt");
								ImGui::EndTooltip();
							}
							if (ImGui::Button("Reset"))
							{
								object->physics.mass = 1.0f;
								object->physics.position = glm::vec3(0.0f);
								object->physics.velocity = glm::vec3(0.0f);
								object->physics.acceleration = glm::vec3(0.0f);
							}
							if (ImGui::IsItemHovered())
							{
								ImGui::BeginTooltip();
								ImGui::Text("Resets whole object");
								ImGui::EndTooltip();
							}

							if (ImGui::TreeNode("Vertices"))
							{
								bool changed = false;
								size_t vertexIndex = 0;
								for (auto& vertex : object->GetMesh()->vertices)
								{
									std::string vertexName = "Vertex " + std::to_string(vertexIndex);
									ImGui::SeparatorText(vertexName.c_str());

									float* position[3] = { &vertex.position.x, &vertex.position.y, &vertex.position.z };
									std::string ID = "##" + std::to_string(objectIndex) + std::to_string(vertexIndex);
									ImGui::PushID(ID.c_str());
									if (ImGui::DragFloat3("Position", *position, 0.01f))
										changed = true;

									float* color[3] = { &vertex.color.x, &vertex.color.y, &vertex.color.z };
									if (ImGui::ColorEdit3("Color", *color))
										changed = true;

									ImGui::PopID();

									vertexIndex++;
								}

								if (changed)
								{
									object->GetMesh()->VBO.Bind();
									object->GetMesh()->VBO.BufferData(object->GetMesh()->vertices);
								}

								ImGui::TreePop();
							}

							ImGui::TreePop();
						}
						objectIndex++;
					}

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Camera"))
				{
					ImGui::SeparatorText("Properties");
					ImGui::DragFloat("FOV", &camera.m_FOV, 1.0f, 50.0f, 110.0f);
					ImGui::DragFloat("Render distance", &camera.m_Far, 1.0f, 1.0f, 1000000.0f);

					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
		}
		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::PollEvents()
{
	if (ImGui::IsKeyPressed(ImGuiKey_Insert))
	{
		show_main_window = !show_main_window;
	}
}

void ImGuiManager::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}