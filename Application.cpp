#include "Application.h"

#define WINDWOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

Application::Application() : camera(WINDWOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 3.0f)), scene(renderer, camera), timeManager()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WINDWOW_WIDTH, WINDOW_HEIGHT, "Simulation", NULL, NULL);
	if (window == nullptr)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();

	imguiManager.Initialize(window);

	glEnable(GL_DEPTH_TEST);

	std::vector<Vertex> verts = {
		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},

		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},
		Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},

		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},

		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},
		Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},

		Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},

		Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},

		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f)},
		Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f)},
		Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f)},

		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f)},
		Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f)},
		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f)},

		Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 1.0f)},

		Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 1.0f)},
		Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 1.0f)},

		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 1.0f)},

		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 1.0f)},
		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 1.0f)}};

	auto mesh = std::make_shared<Mesh>(verts);

	scene.AddObject(mesh);

	auto object1 = make_unique<SceneObject>(mesh);
	object1->physics.SetPosition(glm::vec3(1.0f, 1.0f, 1.0f));
	object1->SetName("Cube");
	scene.AddObject(std::move(object1));

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