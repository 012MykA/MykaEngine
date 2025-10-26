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

	if (show_main_window)
	{
		if (ImGui::Begin("MykaEngine"))
		{
			if (ImGui::BeginTabBar("MainTabBar"))
			{
				if (ImGui::BeginTabItem("Scene"))
				{
					// TODO: remove friend classes at all
					// Properties
					ImGui::SeparatorText("Properties");
					ImGui::Checkbox("Enable global gravity", &scene.physicsEngine.globalGravityEnabled);
					float* gravity[3] = { &scene.physicsEngine.globalGravity.x, &scene.physicsEngine.globalGravity.y, &scene.physicsEngine.globalGravity.z };
					ImGui::DragFloat3("Global gravity", *gravity, 0.1f);


					// Add new object
					ImGui::SeparatorText("Add new Object");
					std::vector<std::string> shapes = { "Cube", "Sphere" };
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

							static bool changed = false;
							static glm::vec3 vertColor = object->GetMesh()->GetVertices().back().color;
							static float color[3] = { vertColor.x, vertColor.y, vertColor.z };
							if (ImGui::ColorEdit3("Object color", color))
							{
								object->GetMesh()->SetGlobalColor(glm::vec3(color[0], color[1], color[2]));

								changed = true;
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

							ImGui::Checkbox("Enable gravity", &object->physics.gravityEnabled);

							// TODO: remove
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
								size_t vertexIndex = 0;
								for (auto& vertex : object->GetMesh()->vertices)
								{
									std::string vertexName = "Vertex " + std::to_string(vertexIndex);
									ImGui::SeparatorText(vertexName.c_str());

									// ID
									std::string ID = "##" + std::to_string(objectIndex) + std::to_string(vertexIndex);
									ImGui::PushID(ID.c_str());

									// Position
									float* position[3] = { &vertex.position.x, &vertex.position.y, &vertex.position.z };
									if (ImGui::DragFloat3("Position", *position, 0.01f))
										changed = true;

									// Color
									float* color[3] = { &vertex.color.x, &vertex.color.y, &vertex.color.z };
									if (ImGui::ColorEdit3("Color", *color))
										changed = true;

									ImGui::PopID();

									vertexIndex++;
								}

								if (ImGui::Button("Update Mesh") && changed)
								{
									object->GetMesh()->VBO.Bind();
									object->GetMesh()->VBO.BufferData(object->GetMesh()->vertices);
									object->GetMesh()->VBO.Unbind();

									changed = false;
								}

								ImGui::SameLine();

								if (ImGui::Button("New Mesh"))
									ImGui::OpenPopup("CreateNewMesh");

								ImVec2 center = ImGui::GetMainViewport()->GetCenter();
								ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

								if (ImGui::BeginPopupModal("CreateNewMesh", NULL, ImGuiWindowFlags_AlwaysAutoResize))
								{
									static char meshName[128] = "";
									ImGui::InputTextWithHint("Mesh name", "Enter mesh name", meshName, IM_ARRAYSIZE(meshName));

									if (ImGui::Button("OK", ImVec2(120, 0)))
									{
										if (std::string(meshName).empty() == false)
										{
											std::shared_ptr<Mesh> newMesh = std::make_shared<Mesh>(object->GetMesh()->GetVertices(), object->GetMesh()->GetIndices());

											newMesh->VBO.Bind();
											newMesh->VBO.BufferData(newMesh->vertices);
											newMesh->VBO.Unbind();

											MeshLibrary::AddMesh((std::string)meshName, newMesh);


											object->SetMesh(MeshLibrary::GetMesh((std::string)meshName));

											ImGui::CloseCurrentPopup();
										}
									}

									ImGui::SetItemDefaultFocus();
									ImGui::SameLine();

									if (ImGui::Button("Cancel", ImVec2(120, 0)))
										ImGui::CloseCurrentPopup();
									ImGui::EndPopup();
								}

								ImGui::TreePop();
							}

							ImGui::TreePop();
						}
						objectIndex++;
					}

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Meshes"))
				{
					ImGui::SeparatorText("Meshes");
					size_t meshIndex = 0;
					for (const auto& [name, mesh] : MeshLibrary::GetAllMeshes())
					{
						std::string meshName = name + "##Mesh";
						if (ImGui::TreeNode(meshName.c_str()))
						{
							bool changed = false;
							static glm::vec3 vertColor = mesh->GetVertices().back().color;
							static float color[3] = { vertColor.x, vertColor.y, vertColor.z };
							if (ImGui::ColorEdit3("Object color", color))
							{
								mesh->SetGlobalColor(glm::vec3(color[0], color[1], color[2]));

								changed = true;
							}

							ImGui::Text("Vertices count: %d", mesh->GetVertices().size());
							if (ImGui::TreeNode("Vertices"))
							{
								size_t vertexIndex = 0;
								for (auto& vertex : mesh->vertices)
								{
									std::string vertexName = "Vertex " + std::to_string(vertexIndex);
									ImGui::SeparatorText(vertexName.c_str());

									// ID
									std::string ID = "##" + std::to_string(meshIndex) + std::to_string(vertexIndex);
									ImGui::PushID(ID.c_str());

									// Position
									float* position[3] = { &vertex.position.x, &vertex.position.y, &vertex.position.z };
									if (ImGui::DragFloat3("Position", *position, 0.01f))
										changed = true;

									// Color
									float* color[3] = { &vertex.color.x, &vertex.color.y, &vertex.color.z };
									if (ImGui::ColorEdit3("Color", *color))
										changed = true;

									if (changed)
									{
										mesh->VBO.Bind();
										mesh->VBO.BufferData(mesh->vertices);
										mesh->VBO.Unbind();
									}

									ImGui::PopID();
									vertexIndex++;
								}
								ImGui::TreePop();
								vertexIndex++;
							}

							ImGui::Text("Indices count: %d", mesh->GetIndices().size());
							ImGui::TreePop();
						}
						meshIndex++;
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