#define _USE_MATH_DEFINES

#include "myka_window.hpp"
#include "myka_material.hpp"
#include "myka_mesh.hpp"
#include "myka_renderer.hpp"
#include "myka_game_object.hpp"
#include "myka_camera.hpp"
#include "myka_timer.hpp"
#include "myka_scene.hpp"
#include "myka_light.hpp"
#include "Deps.hpp"

// std
#include <cmath>

using namespace MykaEngine;

static Mesh getCubeMesh();
static Mesh getCircleMesh();
static Mesh getSphereMesh(float radius, int sectors, int stacks);

int main()
{
    try
    {
        MykaWindow window(WINDOW_WIDTH, WINDOW_HEIGHT, "MykaEngine");
        Renderer renderer;
        Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, window.getWindow());

        Scene scene;
        
        // Blending + Depth
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        std::shared_ptr<Light> mainLight = std::make_shared<Light>(
            glm::vec3(5.0f, 5.0f, 5.0f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3(0.05f, 0.05f, 0.05f),
            glm::vec3(0.8f, 0.8f, 0.8f),
            glm::vec3(1.0f, 1.0f, 1.0f)
        );
        scene.addLight(mainLight);

        // Shaders
        Shader objectShader("../shaders/defaultVert.glsl", "../shaders/defaultFrag.glsl");

        // Meshes
        Mesh skyboxMesh = getSphereMesh(100.0f, 36 * 5, 18 * 5);
        Mesh cubeMesh = getCubeMesh();
        Mesh sphereMesh = getSphereMesh(1.0f, 36, 18);
        
        // Textures
        Texture skyboxTexture("../assets/skyboxes/ocean/skybox.png");
        Texture brickTexture("../assets/brick.png");

        // Materials
        Material skyboxMaterial(std::make_shared<Shader>(objectShader), std::make_shared<Texture>(skyboxTexture));
        Material material(std::make_shared<Shader>(objectShader), std::make_shared<Texture>(brickTexture));

        // GameObjects
        GameObject skybox(std::make_shared<Mesh>(skyboxMesh), std::make_shared<Material>(skyboxMaterial));
        scene.addGameObject(std::make_shared<GameObject>(skybox));

        GameObject cubeObject(std::make_shared<Mesh>(cubeMesh), std::make_shared<Material>(material));
        cubeObject.getTransform().setPosition(glm::vec3(-2.0f, 0.0f, -3.0f));
        scene.addGameObject(std::make_shared<GameObject>(cubeObject));

        GameObject sphereObject(std::make_shared<Mesh>(sphereMesh), std::make_shared<Material>(material));
        sphereObject.getTransform().setPosition(glm::vec3(3.0f, 0.0f, -3.0f));
        scene.addGameObject(std::make_shared<GameObject>(sphereObject));

        double previousTime = glfwGetTime();
        int fps = 0;
        glClearColor(0.20f, 0.20f, 0.20f, 1.0f);
        while (!window.shouldClose())
        {
            double currentTime = glfwGetTime();
            fps++;
            if (currentTime - previousTime >= 1.0)
            {
                window.setWindowTitle(std::format("MykaEngine fps: {}", fps));
                fps = 0;
                previousTime = currentTime;
            }

            // Inputs
            window.pollEvents();
            camera.handleInputs();

            // onUpdate
            Timer::onUpdate();
            camera.onUpdate();

            // onRender
            renderer.clear();
            renderer.drawScene(scene, camera);

            window.swapBuffers();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

Mesh getCubeMesh()
{
    std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},

        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},

        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
        {{-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},

        {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},

        {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},

        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
        {{0.5f, -0.5f, 0.5f}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}}};

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20};

    return {vertices, indices};
}

Mesh getSphereMesh(float radius, int sectors, int stacks)
{
    std::vector<Vertex> vertices{};
    std::vector<GLuint> indices{};

    float stackStep = M_PI / (float)stacks;
    float sectorStep = 2.0f * M_PI / (float)sectors;

    for (int i = 0; i <= stacks; ++i)
    {
        float stackAngle = M_PI / 2.0f - (float)i * stackStep;

        float xz = radius * cos(stackAngle);
        float y = radius * sin(stackAngle);

        for (int j = 0; j <= sectors; ++j)
        {
            float sectorAngle = (float)j * sectorStep;

            float x = xz * cos(sectorAngle);
            float z = xz * sin(sectorAngle);

            glm::vec3 pos = {x, y, z};
            glm::vec3 normal = {x / radius, y / radius, z / radius};

            float u = (float)j / (float)sectors;
            float v = 1.0f - (float)i / (float)stacks;

            vertices.push_back({pos, {u, v}, normal});
        }
    }

    for (int i = 0; i < stacks; ++i)
    {
        int k1 = i * (sectors + 1);
        int k2 = k1 + (sectors + 1);

        for (int j = 0; j < sectors; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stacks - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    return {vertices, indices};
}
