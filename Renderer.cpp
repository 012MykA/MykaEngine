#include "Renderer.h"

Renderer::Renderer() : viewProjection(glm::mat4(1.0f)),
    defaultShader("C:/Users/Vova/source/repos/MykaEngine/defaultVert.glsl", "C:/Users/Vova/source/repos/MykaEngine/defaultFrag.glsl") {
} 
// TODO: Update shader paths

void Renderer::BeginScene(Camera& camera)
{
    viewProjection = camera.GetProjectionMatrix() * camera.GetViewMatrix();

    defaultShader.CompileShaders();
    defaultShader.Use();
}

void Renderer::Submit(SceneObject& object)
{
    object.Draw(defaultShader, viewProjection);
}