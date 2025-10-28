#include "Renderer.h"

Renderer::Renderer()
    : viewProjection(glm::mat4(1.0f)),
      defaultShader("C:/Users/alesh/source/repos/012MykA/MykaEngine/defaultVert.glsl",
                    "C:/Users/alesh/source/repos/012MykA/MykaEngine/defaultFrag.glsl") {}

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
