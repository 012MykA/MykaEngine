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

    void Update(float deltaTime);
    void Render();

public:
    SceneObject& AddObject(std::shared_ptr<Mesh> mesh);
    SceneObject& AddObject(std::unique_ptr<SceneObject> object);

    std::vector<std::unique_ptr<SceneObject>>& GetObjects();

private:
    Renderer& renderer;
    Camera& camera;

    std::vector<std::unique_ptr<SceneObject>> objects;

    glm::vec3 gravity = glm::vec3(0.0f);
};

