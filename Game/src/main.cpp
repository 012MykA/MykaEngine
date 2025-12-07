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
        Texture texture("../assets/brick.png");
        Material material(std::make_shared<Shader>(shader), std::make_shared<Texture>(texture));

        Mesh cubeMesh = getCubeMesh();
        Mesh circleMesh = getCircleMesh();

        GameObject cubeObject(std::make_shared<Mesh>(cubeMesh), std::make_shared<Material>(material));
        cubeObject.getTransform().setPosition(glm::vec3(0.0f, 0.0f, 100.0f));

        GameObject circleObject(std::make_shared<Mesh>(circleMesh), std::make_shared<Material>(material));
        cubeObject.getTransform().setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

        glClearColor(0.20f, 0.20f, 0.20f, 1.0f);
        while (!window.shouldClose())
        {
            // Inputs
            window.pollEvents();
            camera.handleInputs();

            // onUpdate
            Timer::onUpdate();
            camera.onUpdate();
            cubeObject.getTransform().rotate({0.0f, 1.0f, 0.0f});

            // onRender
            renderer.clear();
            renderer.draw(cubeObject, camera);
            renderer.draw(circleObject, camera);

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
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}},

        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
        {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}},

        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}},
        {{-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}},

        {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
        {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}},

        {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}},
        {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}},

        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
        {{0.5f, -0.5f, 0.5f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}}};

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
    
    float radius = 10.0f;
    int res = 100;

    for (int i = 0; i < res; i++)
    {
        float angle = 2.0f * M_PI * (float)(i) / (float)res;
        
        float x = center.position.x + cos(angle) * radius;
        float y = center.position.y + sin(angle) * radius;

        Vertex v{{x, y, 0.0f}, {1.0, 0.0}}; 
        vertices.push_back(v);
    }
    
    for (int i = 1; i <= res; i++)
    {
        indices.push_back(0); 
        indices.push_back(i);
        
        if (i < res) {
            indices.push_back(i + 1);
        } else {
            indices.push_back(1);
        }
    }

    return {vertices, indices};
}