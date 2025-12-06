#include "myka_window.hpp"
#include "Renderer/Material.hpp"
#include "Renderer/Mesh.hpp"
#include "Renderer/Renderer.hpp"

using namespace MykaEngine;

int main()
{
    try
    {
        MykaWindow window(800, 600, "MykaEngine");

        Renderer renderer;

        // Blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Depth
        glEnable(GL_DEPTH_TEST);

        // Mesh
        std::vector<Vertex> vertices = {
            Vertex{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
            Vertex{{-0.5, 0.5f, 0.0f}, {0.0f, 1.0f}},
            Vertex{{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f}},
            Vertex{{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}}
        };
        std::vector<GLuint> indices ={
            0, 1, 2,
            2, 3, 0
        };
        Mesh mesh(vertices, indices);

        // Material
        Shader shader("E:/vscode/MykaEngine/shaders/defaultVert.glsl", "E:/vscode/MykaEngine/shaders/defaultFrag.glsl");
        Texture texture("E:/vscode/MykaEngine/assets/brick.png");
        Material material(std::make_shared<Shader>(shader), std::make_shared<Texture>(texture));

        while (!window.shouldClose())
        {
            renderer.clear();

            renderer.draw(mesh, material);

            window.onUpdate();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}