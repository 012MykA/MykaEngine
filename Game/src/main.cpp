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

int main()
{
    try
    {
        MykaWindow window(WINDOW_WIDTH, WINDOW_HEIGHT, "MykaEngine", true);
        Renderer renderer;
        Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, window.getWindow());

        // Blending + Depth
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        // Light
        Light light = {
            glm::vec3(0.0f),
            glm::vec3(1.0f),
            glm::vec3(0.05f),
            glm::vec3(0.8f),
            glm::vec3(1.0f)};

        Shader lightShader(LIGHT_VERTEX_SHADER_PATH, LIGHT_FRAGMENT_SHADER_PATH);
        Texture sunTexture(SUN_TEXTURE_PATH);
        Material sunMaterial(std::make_shared<Shader>(lightShader), std::make_shared<Texture>(sunTexture));
        Mesh sunMesh = getSphereMesh(SUN_RADIUS, 64, 64);
        GameObject sun(std::make_shared<Mesh>(sunMesh), std::make_shared<Material>(sunMaterial));
        sun.getTransform().setPosition(light.getPosition());

        // Earth
        Mesh earthMesh = getSphereMesh(EARTH_RADIUS, 64, 64);
        Shader objectShader(DEFAULT_VERTEX_SHADER_PATH, DEFAULT_FRAGMENT_SHADER_PATH);
        Texture earthTexture(EARTH_TEXTURE_PATH);
        Material earthMaterial(std::make_shared<Shader>(objectShader), std::make_shared<Texture>(earthTexture));
        GameObject earth(std::make_shared<Mesh>(earthMesh), std::make_shared<Material>(earthMaterial));
        earth.getTransform().setPosition(sun.getTransform().getPosition() + glm::vec3(150.0f, 0.0f, 0.0f));

        camera.setPosition(earth.getTransform().getPosition());

        double previousTime = glfwGetTime();
        int fps = 0;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

            earth.getTransform().rotate(glm::vec3(0.0f, 1.0f, 0.0f));

            sun.getTransform().rotate(glm::vec3(0.0f, 1.0f, 0.0f) * Timer::getDeltaTime());

            // onRender
            renderer.clear();
            { // Object
                GameObject object = earth;

                const auto &transform = object.getTransform();
                const auto &material = object.getMaterial();
                const auto &mesh = object.getMesh();

                glm::mat4 model = transform.getModelMatrix();
                glm::mat4 view = camera.getViewMatrix();
                glm::mat4 proj = camera.getProjectionMatrix();

                material->bindShader();

                glm::mat4 mvp = proj * view * model;
                glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));

                material->m_Shader->setUniformMat4f("u_MVP", mvp);
                material->m_Shader->setUniformMat4f("u_Model", model);
                material->m_Shader->setUniform1i("u_Texture", 0);
                material->m_Shader->setUniform3f("u_LightColor", light.getColor());
                material->m_Shader->setUniform3f("u_ObjectColor", object.getMaterial()->getColor());
                material->m_Shader->setUniform3f("u_LightPos", light.getPosition());
                material->m_Shader->setUniform3f("u_ViewPos", camera.getPosition());

                material->bindTexture();

                mesh->bind();

                glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->getIndexCount()), GL_UNSIGNED_INT, 0);

                mesh->unbind();
            }

            { // light
                GameObject object = sun;

                const auto &transform = object.getTransform();
                const auto &material = object.getMaterial();
                const auto &mesh = object.getMesh();

                glm::mat4 model = transform.getModelMatrix();
                glm::mat4 view = camera.getViewMatrix();
                glm::mat4 proj = camera.getProjectionMatrix();

                material->bindShader();

                glm::mat4 mvp = proj * view * model;

                material->m_Shader->setUniformMat4f("u_MVP", mvp);
                material->m_Shader->setUniform1i("u_Texture", 0);
                material->m_Shader->setUniform3f("u_LightColor", light.getColor());

                material->bindTexture();

                mesh->bind();

                glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->getIndexCount()), GL_UNSIGNED_INT, 0);

                mesh->unbind();
            }

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
