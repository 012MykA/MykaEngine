#pragma once

#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"
#include "SceneObject.h"

class Renderer
{
public:
    Renderer();
    void BeginScene(Camera& camera);
    void Submit(SceneObject& object);

private:
    Shader defaultShader;
    glm::mat4 viewProjection;
};
