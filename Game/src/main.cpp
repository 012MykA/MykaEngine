#define _USE_MATH_DEFINES

#include "myka_window.hpp"
#include "myka_material.hpp"
#include "myka_mesh.hpp"
#include "myka_renderer.hpp"
#include "myka_game_object.hpp"
#include "myka_camera.hpp"
#include "myka_timer.hpp"

#include "Deps.hpp"

// std
#include <cmath>

using namespace MykaEngine;

static Mesh getCubeMesh();
static Mesh getCircleMesh();
static Mesh getSphereMesh(float radius, int sectors, int stacks);

struct Light
{
    Light(Mesh mesh) : m_Mesh(mesh) {}

    Mesh m_Mesh;
    glm::vec3 m_Position;

    glm::vec3 m_Color;

    glm::vec3 m_Ambient;
    glm::vec3 m_Diffuse;
    glm::vec3 m_Specular;
};

int main()
{
    try
    {
        MykaWindow window(WINDOW_WIDTH, WINDOW_HEIGHT, "MykaEngine");

        Renderer renderer;
        Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, window.getWindow());

        // Blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Depth
        glEnable(GL_DEPTH_TEST);

        Shader shader("../shaders/defaultVert.glsl", "../shaders/defaultFrag.glsl");

        // Skybox
        Mesh skyboxMesh = getSphereMesh(100.0f, 36 * 5, 18 * 5);
        Texture skyboxTexture("../assets/skyboxes/ocean/skybox.png");
        Material skyboxMaterial(std::make_shared<Shader>(shader), std::make_shared<Texture>(skyboxTexture));
        GameObject skybox(std::make_shared<Mesh>(skyboxMesh), std::make_shared<Material>(skyboxMaterial));

        Texture texture("../assets/brick.png");
        Material material(std::make_shared<Shader>(shader), std::make_shared<Texture>(texture));

        Mesh cubeMesh = getCubeMesh();
        Mesh circleMesh = getCircleMesh();
        Mesh sphereMesh = getSphereMesh(1.0f, 36, 18);

        GameObject cubeObject(std::make_shared<Mesh>(cubeMesh), std::make_shared<Material>(material));
        cubeObject.getTransform().setPosition(glm::vec3(-2.0f, 0.0f, -3.0f));

        GameObject circleObject(std::make_shared<Mesh>(circleMesh), std::make_shared<Material>(material));
        circleObject.getTransform().setPosition(glm::vec3(0.0f, 0.0f, -3.0f));

        GameObject sphereObject(std::make_shared<Mesh>(sphereMesh), std::make_shared<Material>(material));
        sphereObject.getTransform().setPosition(glm::vec3(3.0f, 0.0f, -3.0f));

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
            renderer.draw(skybox, camera);

            renderer.draw(cubeObject, camera);
            renderer.draw(circleObject, camera);
            renderer.draw(sphereObject, camera);

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

        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {
                                                 0.0f,
                                                 0.0f,
                                                 -1.0f,
                                             }},
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, {
                                                  0.0f,
                                                  0.0f,
                                                  -1.0f,
                                              }},
        {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}, {
                                                 0.0f,
                                                 0.0f,
                                                 -1.0f,
                                             }},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}, {
                                                0.0f,
                                                0.0f,
                                                -1.0f,
                                            }},

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

Mesh getCircleMesh()
{
    std::vector<Vertex> vertices{};
    std::vector<GLuint> indices{};

    Vertex center{{0.0f, 0.0f, 0.0f}, {0.5f, 0.5f}};
    vertices.push_back(center);

    float radius = 1.0f;
    int res = 36;

    for (int i = 0; i < res; i++)
    {
        float angle = 2.0f * M_PI * (float)(i) / (float)res;

        float x = center.position.x + cos(angle) * radius;
        float z = center.position.z + sin(angle) * radius;

        Vertex v{{x, 0.0f, z}, {1.0, 0.0}};
        vertices.push_back(v);
    }

    for (int i = 1; i <= res; i++)
    {
        indices.push_back(0);
        indices.push_back(i);

        if (i < res)
        {
            indices.push_back(i + 1);
        }
        else
        {
            indices.push_back(1);
        }
    }

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