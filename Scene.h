#pragma once

#include "Renderer.h"
#include "Camera.h"
#include "SceneObject.h"
#include <vector>
#include <memory>

class Scene
{
public:
    Scene(Renderer& renderer, Camera& camera);

    SceneObject& AddObject(std::shared_ptr<Mesh> mesh);

    void Update(float deltaTime);
    void Render();

    glm::vec3 gravity = glm::vec3(0.0f);

private:
    Renderer& renderer;
    Camera& camera;
    std::vector<std::unique_ptr<SceneObject>> objects;
};

