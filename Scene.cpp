#include "Scene.h"

Scene::Scene(PhysicsEngine& physicsEngine, Renderer& renderer, Camera& camera) : physicsEngine(physicsEngine), renderer(renderer), camera(camera) {}

SceneObject& Scene::AddObject(std::shared_ptr<Mesh> mesh)
{
    objects.push_back(std::make_unique<SceneObject>(std::move(mesh)));
    return *objects.back();
}

SceneObject& Scene::AddObject(std::unique_ptr<SceneObject> object)
{
    physicsEngine.AddObject(&(*object).physics);
    objects.push_back(std::move(object));
    return *objects.back();
}

std::vector<std::unique_ptr<SceneObject>>& Scene::GetObjects()
{
	return objects;
}

void Scene::Update(float deltaTime)
{
    physicsEngine.Update(deltaTime);
}

void Scene::Render()
{
    renderer.BeginScene(camera);

    for (auto& obj : objects)
        renderer.Submit(*obj);
}