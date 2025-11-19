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
					// Properties
					ImGui::SeparatorText("Properties");
					ImGui::Checkbox("Enable global gravity", &scene.physicsEngine.globalGravityEnabled);
					float* gravity[3] = { &scene.physicsEngine.globalGravity.x, &scene.physicsEngine.globalGravity.y, &scene.physicsEngine.globalGravity.z };
					ImGui::DragFloat3("Global gravity", *gravity, 0.1f);


					// Add new object
					ImGui::SeparatorText("Add new Object");

					static char objectName[128] = "";
					static int current_mesh_index = 0;
					std::vector<std::string> meshNames;

					for (auto& pair : MeshLibrary::GetAllMeshes())
					{
						meshNames.push_back(pair.first);
					}

					ImGui::InputText("Object name", objectName, IM_ARRAYSIZE(objectName));

					if (!meshNames.empty())
					{
						const char* preview_value = meshNames[current_mesh_index].c_str();

						if (ImGui::BeginCombo("Mesh for new object", preview_value))
						{
							for (int n = 0; n < meshNames.size(); n++)
							{
								bool is_selected = (current_mesh_index == n);
								if (ImGui::Selectable(meshNames[n].c_str(), is_selected))
									current_mesh_index = n;
								if (is_selected)
									ImGui::SetItemDefaultFocus();
							}
							ImGui::EndCombo();
						}

						if (ImGui::Button("Create New Object"))
						{
							std::shared_ptr<Mesh> mesh = MeshLibrary::GetMesh(meshNames[current_mesh_index]);

							std::unique_ptr<SceneObject> newObject = std::make_unique<SceneObject>(mesh);

							std::string finalName = (std::string)objectName;
							if (finalName.empty())
								finalName = "UnnamedObject";

							newObject->SetName(finalName);

							scene.AddObject(std::move(newObject));
							
							objectName[0] = '\0';
						}
					}
					else
					{
						ImGui::Text("No meshes available. Create a mesh first.");
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
							ImGui::DragFloat("Elasticity", &object->physics.elasticity, 0.01f, 0.0f, 1.0f);

							// Position
							ImGui::SeparatorText("Kinematics");
							float* position[3] = { &object->physics.position.x, &object->physics.position.y, &object->physics.position.z };
							ImGui::DragFloat3("Position", *position, 0.1f);
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

							// Immovable checkbox
							ImGui::Checkbox("Immovable", &object->physics.immovable);
							if (ImGui::IsItemHovered())
							{
								ImGui::BeginTooltip();
								ImGui::Text("When enabled, object ignores forces, gravity and won't be moved by collisions.");
								ImGui::EndTooltip();
							}

							if (ImGui::Button("Reset"))
							{
								object->physics.position = glm::vec3(0.0f);
								object->physics.velocity = glm::vec3(0.0f);
							}
							if (ImGui::IsItemHovered())
							{
								ImGui::BeginTooltip();
								ImGui::Text("Resets whole object");
								ImGui::EndTooltip();
							}

							// Mesh
							ImGui::SeparatorText("Using mesh");

							std::vector<std::string> meshNames;

							for (auto pair : MeshLibrary::GetAllMeshes())
							{
								meshNames.push_back(pair.first);
							}

							auto currentMeshIter = std::find(meshNames.begin(), meshNames.end(), object->GetMesh()->GetName());

							int currentMeshIndex = -1;
							if (currentMeshIter != meshNames.end())
								currentMeshIndex = std::distance(meshNames.begin(), currentMeshIter);

							const char* preview_value = meshNames[currentMeshIndex].c_str();
							if (ImGui::BeginCombo("##Mesh", preview_value))
							{
								for (int n = 0; n < meshNames.size(); n++)
								{
									bool is_selected = (currentMeshIndex == n);

									if (ImGui::Selectable(meshNames[n].c_str(), is_selected))
									{
										currentMeshIndex = n;

										auto mesh = MeshLibrary::GetMesh(meshNames[n]);

										object->SetMesh(mesh);
									}

									if (is_selected)
										ImGui::SetItemDefaultFocus();
								}
								ImGui::EndCombo();
							}

							ImGui::SeparatorText("Resize");

							float objectScale[3] = {object->physics.GetLocalAABB().max.x - object->physics.GetLocalAABB().min.x,
												  object->physics.GetLocalAABB().max.y - object->physics.GetLocalAABB().min.y,
												  object->physics.GetLocalAABB().max.z - object->physics.GetLocalAABB().min.z };
							if (ImGui::DragFloat3("Object Scale", objectScale));
							if (ImGui::IsItemHovered())
							{
								ImGui::BeginTooltip();
								ImGui::Text("To change Scale use drag bellow");
								ImGui::EndTooltip();
							}


							static glm::vec3 scaleVector = glm::vec3(1.0f);
							float scale[3] = { scaleVector.x, scaleVector.y, scaleVector.z };

							if (ImGui::DragFloat3("Scale (X, Y, Z)", scale, 0.01f, 0.01f, 10.0f))
							{
								scaleVector = glm::vec3(scale[0], scale[1], scale[2]);

								object->physics.ApplyAABBScale(scaleVector);
								object->GetMesh()->ApplyScale(scaleVector);

								object->GetMesh()->VBO.Bind();
								object->GetMesh()->VBO.BufferData(object->GetMesh()->GetVertices());
								object->GetMesh()->VBO.Unbind();
							}

							scaleVector = glm::vec3(1.0f);

							ImGui::TreePop();
						}
						objectIndex++;
					}

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Meshes"))
				{
					ImGui::SeparatorText("Create Mesh");

					if (ImGui::Button("New Mesh"))
						ImGui::OpenPopup("CreateNewMesh");

					ImVec2 center = ImGui::GetMainViewport()->GetCenter();
					ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

					if (ImGui::BeginPopupModal("CreateNewMesh", NULL, ImGuiWindowFlags_AlwaysAutoResize))
					{
						static char meshName[128] = "";
						static int base_mesh_index = 0;

						std::vector<std::string> meshNames;

						for (const auto& pair : MeshLibrary::GetAllMeshes())
						{
							meshNames.push_back(pair.first);
						}

						ImGui::InputTextWithHint("New Mesh name", "Enter unique name", meshName, IM_ARRAYSIZE(meshName));

						ImGui::Separator();

						if (!meshNames.empty())
						{
							if (base_mesh_index >= meshNames.size()) base_mesh_index = 0;

							const char* preview_base_mesh = meshNames[base_mesh_index].c_str();
							if (ImGui::BeginCombo("Base Mesh to Duplicate", preview_base_mesh))
							{
								for (int n = 0; n < meshNames.size(); n++)
								{
									bool is_selected = (base_mesh_index == n);
									if (ImGui::Selectable(meshNames[n].c_str(), is_selected))
										base_mesh_index = n;
									if (is_selected)
										ImGui::SetItemDefaultFocus();
								}
								ImGui::EndCombo();
							}
							if (ImGui::IsItemHovered())
							{
								ImGui::BeginTooltip();
								ImGui::Text("The new mesh will be a copy of the selected base mesh.");
								ImGui::EndTooltip();
							}
						}
						else
						{
							ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "No existing meshes to duplicate.");
						}

						ImGui::Separator();

						if (ImGui::Button("Create", ImVec2(120, 0)))
						{
							std::string name = (std::string)meshName;
							bool can_create = !name.empty() && !meshNames.empty();

							if (can_create)
							{
								std::shared_ptr<Mesh> baseMesh = MeshLibrary::GetMesh(meshNames[base_mesh_index]);

								if (baseMesh)
								{
									std::vector<Vertex> vertices = baseMesh->GetVertices();
									std::vector<GLuint> indices = baseMesh->GetIndices();

									std::shared_ptr<Mesh> newMesh;
									if (indices.empty())
										newMesh = std::make_shared<Mesh>(vertices);
									else
										newMesh = std::make_shared<Mesh>(vertices, indices);

									newMesh->SetName(name);
									MeshLibrary::AddMesh(name, newMesh);

									meshName[0] = '\0';
									ImGui::CloseCurrentPopup();
								}
							}
						}

						ImGui::SetItemDefaultFocus();
						ImGui::SameLine();

						if (ImGui::Button("Cancel", ImVec2(120, 0)))
						{
							meshName[0] = '\0';
							ImGui::CloseCurrentPopup();
						}
						ImGui::EndPopup();
					}					

					// Meshes
					ImGui::SeparatorText("Meshes");
					size_t meshIndex = 0;
					for (const auto& [name, mesh] : MeshLibrary::GetAllMeshes())
					{
						std::string meshName = name + "##Mesh";
						if (ImGui::TreeNode(meshName.c_str()))
						{
							bool changed = false;
							glm::vec3 vertColor = mesh->GetVertices().back().color;
							float color[3] = { vertColor.x, vertColor.y, vertColor.z };
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
									if (ImGui::IsItemHovered())
									{
										ImGui::BeginTooltip();
										ImGui::Text("Use with caution");
										ImGui::EndTooltip();
									}

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
					// Position
					ImGui::SeparatorText("Kinematics");
					float* position[3] = { &camera.m_Position.x, &camera.m_Position.y, &camera.m_Position.z };
					ImGui::DragFloat3("Position", *position, 0.1f);
					ImGui::Separator();

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