#include "Renderer.h"

Renderer::Renderer()
    : viewProjection(glm::mat4(1.0f)),
      defaultShader("C:/Users/Vova/source/repos/MykaEngine 2.0/defaultVert.glsl",
                    "C:/Users/Vova/source/repos/MykaEngine 2.0/defaultFrag.glsl") {}

void Renderer::BeginScene(Camera& camera)
{
    viewProjection = camera.m_ProjectionMatrix * camera.m_ViewMatrix;
    defaultShader.CompileShaders();
    defaultShader.Use();
}

void Renderer::Submit(SceneObject& object)
{
    object.Draw(defaultShader, viewProjection);
}