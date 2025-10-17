#include "Application.h"

Application::Application() : camera(800, 600, glm::vec3(0.0f, 0.0f, 3.0f)), scene(renderer, camera), timeManager()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "Simulation", NULL, NULL);
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
		// front
		Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},

		Vertex{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 1.0f)},

		// back
		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 1.0f)},

		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 1.0f)},

		// right
		 Vertex{glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 1.0f)},
		 Vertex{glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 1.0f)},

		 Vertex{glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 1.0f)},
		 Vertex{glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 0.0f)},

		 // left
		 Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 0.0f)},
		 Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 1.0f)},
		 Vertex{glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 1.0f)},

		 Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 0.0f)},
		 Vertex{glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 1.0f)},
		 Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 0.0f)},

		 // top
		 Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},

		 Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},
		 Vertex{glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 1.0f)},

		 // bottom
		 Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(0.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},

		 Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(0.0f, 0.0f)},
		 Vertex{glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},
		 Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec2(0.0f, 1.0f)}
	};

	Texture brick("C:/Users/Vova/source/repos/MykaEngine/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE); // TODO: pathes
	Shader shader("C:/Users/Vova/source/repos/MykaEngine/defaultVert.glsl", "C:/Users/Vova/source/repos/MykaEngine/defaultFrag.glsl"); // TODO: pathes

	auto mesh = std::make_shared<Mesh>(verts, brick);

	scene.AddObject(mesh);
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

	imguiManager.Render();
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

	camera.Inputs(window, deltaTime);
}

void Application::Run()
{
	while (!glfwWindowShouldClose(window))
	{
		OnUpdate();
	}
}