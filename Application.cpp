#include "Application.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

Application::Application() : camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 3.0f)), scene(renderer, camera), timeManager()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Simulation", NULL, NULL);
	if (window == nullptr)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();

	MeshLibrary::Initialize();
	imguiManager.Initialize(window);

	glEnable(GL_DEPTH_TEST);

	{
		auto cube = std::make_unique<SceneObject>(MeshLibrary::GetMesh("Cube"));
		cube->SetName("Cube");
		scene.AddObject(std::move(cube));
	}

	{
		// TODO: Scene::CreateBorders();
		// Scene borders
		auto sceneVerts = MeshLibrary::GetMesh("Cube")->GetVertices();
		auto sceneIndices = MeshLibrary::GetMesh("Cube")->GetIndices();

		for (auto& v : sceneVerts)
		{
			v.position *= 10.0f;
			v.color = glm::vec3(1.0f, 0.0f, 0.0f);
		}

		//MeshLibrary::AddMesh("SceneBorders", std::make_shared<Mesh>(sceneVerts, sceneIndices));
		auto mesh = std::make_shared<Mesh>(sceneVerts, sceneIndices);
		mesh->SetDrawMode(GL_LINES);

		auto borders = std::make_unique<SceneObject>(mesh);
		borders->physics.SetGravityEnabled(false);
		borders->SetName("Borders");
		scene.AddObject(std::move(borders));
	}
}

Application::~Application()
{
	imguiManager.Shutdown();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void Application::OnUpdate()
{
	timeManager.UpdateDeltaTime();
	imguiManager.NewFrame();
	float deltaTime = timeManager.GetDeltaTime();
	PollEvents(deltaTime);
	camera.UpdateMatrices();
	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene.Render();
	scene.Update(deltaTime);

	imguiManager.Render(scene, camera);
	glfwPollEvents();
	glfwSwapBuffers(window);
}

void Application::PollEvents(float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		glEnable(GL_POLYGON_SMOOTH);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE)
	{
		glDisable(GL_POLYGON_SMOOTH);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	imguiManager.PollEvents();
	camera.Inputs(window, deltaTime);
}

void Application::Run()
{
	while (!glfwWindowShouldClose(window))
	{
		OnUpdate();
	}
}