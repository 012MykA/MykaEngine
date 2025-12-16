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
#include <random>
#include <ctime>

using namespace MykaEngine;

static std::shared_ptr<Mesh> getPlatformMesh();
static std::shared_ptr<Mesh> getCubeMesh();
static std::shared_ptr<Mesh> getSphereMesh(float radius, int sectors, int stacks);

static void setLightUniforms(Material &material, const Light &light);

int main()
{
    try
    {
        MykaWindow window(WINDOW_WIDTH, WINDOW_HEIGHT, "MykaEngine", true);
        Renderer renderer;
        Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, window.getWindow());
        Scene scene;

        // Blending + Depth
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        // Light
        std::shared_ptr<Light> light = std::make_shared<Light>(
            glm::vec3(2.0f),
            glm::vec3(0.1f), // Ambient
            glm::vec3(0.8f), // Diffuse
            glm::vec3(1.0f)  // Specular
        );
        scene.addLight(light);

        Shader lightShader(LIGHT_VERTEX_SHADER_PATH, LIGHT_FRAGMENT_SHADER_PATH);
        Material lightMaterial(std::make_shared<Shader>(lightShader));
        std::shared_ptr<Mesh> lightMesh = getSphereMesh(0.2, 32, 32);

        std::shared_ptr<GameObject> lightSphere = std::make_shared<GameObject>(lightMesh, std::make_shared<Material>(lightMaterial));
        lightSphere->getTransform().setPosition(light->getPosition());
        scene.addGameObject(lightSphere);

        Shader colorShader(COLOR_VERTEX_SHADER_PATH, COLOR_FRAGMENT_SHADER_PATH);
        Shader texShader(TEX_VERTEX_SHADER_PATH, TEX_FRAGMENT_SHADER_PATH);

        std::shared_ptr<Texture> boxTexture = std::make_shared<Texture>(BOX_TEXTURE_PATH);
        std::shared_ptr<Texture> boxSpecularTexture = std::make_shared<Texture>(BOX_SPECULAR_TEXTURE_PATH);

        // Materials
        std::shared_ptr<Material> boxMaterial = std::make_shared<Material>(std::make_shared<Shader>(texShader));
        boxMaterial->setTexture("u_Material.diffuse", boxTexture);
        boxMaterial->setTexture("u_Material.specular", boxSpecularTexture);
        boxMaterial->setUniform("u_Material.shininess", 76.8f);

        // Meshes
        std::shared_ptr<Mesh> cubeMesh = getCubeMesh();

        // Objects
        // for (int i = 0; i < 10; ++i)
        // {
        //     std::shared_ptr<GameObject> box = std::make_shared<GameObject>(cubeMesh, boxMaterial);

        //     float x = rand() % 10;
        //     float y = rand() % 10;
        //     float z = rand() % 10;

        //     box->getTransform().setPosition({x, y, z});

        //     scene.addGameObject(box);
        // }

        std::shared_ptr<GameObject> box = std::make_shared<GameObject>(cubeMesh, boxMaterial);
        box->getTransform().setPosition(glm::vec3(0.0f));
        scene.addGameObject(box);

        std::srand(std::time(nullptr));
        // std::vector<float> offsets;
        // for (int i = 0; i < scene.getGameObjects().size(); i++)
        // {
        //     offsets.push_back(static_cast<float>(std::rand() % 100));
        // }

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
                std::cout << "FPS: " << fps << std::endl;
                fps = 0;
                previousTime = currentTime;
            }

            // Inputs
            window.pollEvents();
            camera.handleInputs();

            // onUpdate
            Timer::onUpdate();
            camera.onUpdate();

            // float time = static_cast<float>(glfwGetTime());
            // int i = 0;
            // for (auto &box : scene.getGameObjects())
            // {
            //     float off = offsets[i];

            //     float rx = sin(time * 0.5f + off) * 1.5f;
            //     float ry = cos(time * 0.3f + off * 0.5f) * 1.2f;
            //     float rz = sin(time * 0.7f + off * 2.0f) * 1.0f;

            //     box->getTransform().rotate(glm::vec3(rx, ry, rz));
            //     i++;
            // }

            // float x = cos(glfwGetTime() * 1.0f) * 2.0f;
            // float z = sin(glfwGetTime() * 1.0f) * 2.0f;

            // light->setPosition({x, 0.0f, z});
            // lightSphere->getTransform().setPosition(light->getPosition());

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

std::shared_ptr<Mesh> getPlatformMesh()
{
    std::vector<Vertex> vertices = {
        {{-0.5f, 0.0f, 0.5f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, 0.0f, -0.5f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.0f, -0.5f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.0f, 0.5f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
    };

    std::vector<GLuint> indices = {0, 1, 2, 2, 3, 0};

    return std::make_shared<Mesh>(vertices, indices);
}

std::shared_ptr<Mesh> getCubeMesh()
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
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
    };

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20};

    return std::make_shared<Mesh>(vertices, indices);
}

std::shared_ptr<Mesh> getSphereMesh(float radius, int sectors, int stacks)
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

    return std::make_shared<Mesh>(vertices, indices);
}

void setLightUniforms(Material &material, const Light &light)
{
    material.setUniform("u_Light.position", light.getPosition());
    material.setUniform("u_Light.ambient", light.getAmbient());
    material.setUniform("u_Light.diffuse", light.getDiffuse());
    material.setUniform("u_Light.specular", light.getSpecular());
}
