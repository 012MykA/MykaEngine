#pragma once

#include "Renderer.h"
#include "PhysicsEngine.h"
#include "Camera.h"
#include "SceneObject.h"

#include <vector>
#include <memory>

class Scene
{
public:
    Scene(PhysicsEngine& physicsEngine, Renderer& renderer, Camera& camera);

    void Update(float deltaTime);
    void Render();

	friend class ImGuiManager;
public:
    SceneObject& AddObject(std::shared_ptr<Mesh> mesh);
    SceneObject& AddObject(std::unique_ptr<SceneObject> object);

    std::vector<std::unique_ptr<SceneObject>>& GetObjects();

private:
	PhysicsEngine& physicsEngine;
    Renderer& renderer;
    Camera& camera;

    std::vector<std::unique_ptr<SceneObject>> objects;
};
