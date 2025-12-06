#include "myka_window.hpp"
#include "Renderer/Material.hpp"
#include "Renderer/Mesh.hpp"
#include "Renderer/Renderer.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include "Deps.hpp"
#include "Timer.hpp"

using namespace MykaEngine;

int main()
{
    try
    {
        MykaWindow window(WINDOW_WIDTH, WINDOW_HEIGHT, "MykaEngine");

        Renderer renderer;

        // Blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Depth
        glEnable(GL_DEPTH_TEST);

        // Mesh
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
            {{-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}}
        };

        std::vector<unsigned int> indices = {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4,
            8, 9, 10, 10, 11, 8,
            12, 13, 14, 14, 15, 12,
            16, 17, 18, 18, 19, 16,
            20, 21, 22, 22, 23, 20
        };
        Mesh mesh(vertices, indices);
        
        // Material
        Shader shader("E:/vscode/MykaEngine/shaders/defaultVert.glsl", "E:/vscode/MykaEngine/shaders/defaultFrag.glsl");
        Texture texture("E:/vscode/MykaEngine/assets/brick.png");
        Material material(std::make_shared<Shader>(shader), std::make_shared<Texture>(texture));
        
        GameObject gameObject(std::make_shared<Mesh>(mesh), std::make_shared<Material>(material));

        
        Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, window.getWindow());
        
        glClearColor(0.20f, 0.20f, 0.20f, 1.0f);
        while (!window.shouldClose())
        {
            // Inputs
            window.pollEvents();
            camera.handleInputs();

            // onUpdate
            Timer::onUpdate();

            camera.onUpdate();

            // onRender
            renderer.clear();

            renderer.draw(mesh, material);

            window.swapBuffers();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}