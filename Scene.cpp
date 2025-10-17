#include "Scene.h"

Scene::Scene(Renderer& renderer, Camera& camera)
    : renderer(renderer), camera(camera) {}

SceneObject& Scene::AddObject(std::shared_ptr<Mesh> mesh)
{
    objects.push_back(std::make_unique<SceneObject>(std::move(mesh)));
    return *objects.back();
}

void Scene::Update(float deltaTime)
{
    for (auto& obj : objects)
        obj->Update(deltaTime);
}

void Scene::Render()
{
    renderer.BeginScene(camera);
    for (auto& obj : objects)
        renderer.Submit(*obj);
}