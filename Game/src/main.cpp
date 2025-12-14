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

static Mesh getPlatformMesh();
static Mesh getCubeMesh();
static Mesh getSphereMesh(float radius, int sectors, int stacks);

static void setLightUniforms(Material& material, const Light &light);

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
        Light light = {
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.2f),
            glm::vec3(0.5f),
            glm::vec3(1.0f)};

        Shader lightShader(LIGHT_VERTEX_SHADER_PATH, LIGHT_FRAGMENT_SHADER_PATH);
        Material lightMaterial(std::make_shared<Shader>(lightShader));
        Mesh sphereMesh = getSphereMesh(0.2, 32, 32);
        GameObject lightSphere(std::make_shared<Mesh>(sphereMesh), std::make_shared<Material>(lightMaterial));
        lightSphere.getTransform().setPosition(light.getPosition());
        scene.addGameObject(std::make_shared<GameObject>(lightSphere));
        
        Shader objectShader(DEFAULT_VERTEX_SHADER_PATH, DEFAULT_FRAGMENT_SHADER_PATH);
        
        // Materials
        Material emerald(std::make_shared<Shader>(objectShader));
        emerald.setUniform("u_Material.ambient", glm::vec3(0.0215, 0.1745, 0.0215));
        emerald.setUniform("u_Material.diffuse", glm::vec3(0.07568, 0.61424, 0.07568));
        emerald.setUniform("u_Material.specular", glm::vec3(0.633, 0.727811, 0.633));
        emerald.setUniform("u_Material.shininess", 0.6f * 128.0f);
        setLightUniforms(emerald, light);
        
        Material ruby(std::make_shared<Shader>(objectShader));
        ruby.setUniform("u_Material.ambient", glm::vec3(0.1745, 0.01175, 0.01175));
        ruby.setUniform("u_Material.diffuse", glm::vec3(0.61424, 0.04136, 0.04136));
        ruby.setUniform("u_Material.specular", glm::vec3(0.727811, 0.626959, 0.626959));
        ruby.setUniform("u_Material.shininess", 0.6f * 128.0f);
        setLightUniforms(ruby, light);

        Material cyanPlastic(std::make_shared<Shader>(objectShader));
        cyanPlastic.setUniform("u_Material.ambient", glm::vec3(0.0, 0.1, 0.06));
        cyanPlastic.setUniform("u_Material.diffuse", glm::vec3(0.0, 0.50980392, 0.50980392));
        cyanPlastic.setUniform("u_Material.specular", glm::vec3(0.50196078, 0.50196078, 0.50196078));
        cyanPlastic.setUniform("u_Material.shininess", 0.25f * 128.0f);
        setLightUniforms(cyanPlastic, light);

        Material yellowRubber(std::make_shared<Shader>(objectShader));
        yellowRubber.setUniform("u_Material.ambient", glm::vec3(0.05, 0.05, 0.0));
        yellowRubber.setUniform("u_Material.diffuse", glm::vec3(0.5, 0.5, 0.4));
        yellowRubber.setUniform("u_Material.specular", glm::vec3(0.7, 0.7, 0.04));
        yellowRubber.setUniform("u_Material.shininess", 0.078125f * 128.0f);
        setLightUniforms(yellowRubber, light);

        // Meshes
        Mesh objectsMesh = getSphereMesh(0.5f, 64, 64);

        // Objects
        GameObject emeraldCube(std::make_shared<Mesh>(objectsMesh), std::make_shared<Material>(emerald));
        emeraldCube.getTransform().setPosition(glm::vec3(2.0f, 0.0f, 0.0f));

        GameObject rubyCube(std::make_shared<Mesh>(objectsMesh), std::make_shared<Material>(ruby));
        rubyCube.getTransform().setPosition(glm::vec3(-2.0f, 0.0f, 0.0f));

        GameObject cyanPlasticCube(std::make_shared<Mesh>(objectsMesh), std::make_shared<Material>(cyanPlastic));
        cyanPlasticCube.getTransform().setPosition(glm::vec3(0.0f, 0.0f, 2.0f));

        GameObject yellowRubberCube(std::make_shared<Mesh>(objectsMesh), std::make_shared<Material>(yellowRubber));
        yellowRubberCube.getTransform().setPosition(glm::vec3(0.0f, 0.0f, -2.0f));

        scene.addGameObject(std::make_shared<GameObject>(emeraldCube));
        scene.addGameObject(std::make_shared<GameObject>(rubyCube));
        scene.addGameObject(std::make_shared<GameObject>(cyanPlasticCube));
        scene.addGameObject(std::make_shared<GameObject>(yellowRubberCube));

        camera.setPosition(glm::vec3(0.0f, 1.0f, 2.0f));

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

Mesh getPlatformMesh()
{
    std::vector<Vertex> vertices = {
        {{-0.5f, 0.0f, 0.5f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, 0.0f, -0.5f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.0f, -0.5f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.0f, 0.5f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
    };

    std::vector<GLuint> indices = {0, 1, 2, 2, 3, 0};

    return {vertices, indices};
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
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
    };

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

void setLightUniforms(Material& material, const Light &light)
{
    material.setUniform("u_Light.position", light.getPosition());
    material.setUniform("u_Light.ambient", light.getAmbient());
    material.setUniform("u_Light.diffuse", light.getDiffuse());
    material.setUniform("u_Light.specular", light.getSpecular());
}
