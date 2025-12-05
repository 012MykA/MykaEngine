#include "myka_window.hpp"
#include "Renderer/Material.hpp"
#include "Renderer/Mesh.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/Renderer.hpp"

#include <stb_image.h>

using namespace MykaEngine;


int main()
{
    try
    {
        MykaWindow window(800, 600, "MykaEngine");

        glEnable(GL_BLEND);
        
        Renderer renderer;
        Shader shader("E:/vscode/MykaEngine/shaders/defaultVert.glsl", "E:/vscode/MykaEngine/shaders/defaultFrag.glsl");
        
        std::vector<Vertex> vertices = {
            Vertex{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
            Vertex{{-0.5, 0.5f, 0.0f}, {0.0f, 1.0f}},
            Vertex{{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f}},
            Vertex{{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}}
        };
        std::vector<GLuint> indices = {
            0, 1, 2,
            2, 3, 0
        };
        Material material(std::make_shared<Shader>(shader));

        Mesh mesh(vertices, indices);
        
        shader.use();
        shader.setUniform3f("u_Color", glm::vec3(0.5f, 0.0f, 0.5f));
        
        Texture texture("E:/vscode/MykaEngine/assets/brick.png");
        texture.bind();
        shader.setUniform1i("u_Texture", 0);
        
        while (!window.shouldClose())
        {
            renderer.clear();

            renderer.draw(mesh.m_VAO, mesh.m_IBO, shader);

            window.onUpdate();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}