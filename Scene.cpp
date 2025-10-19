#include "Scene.h"

Scene::Scene(Renderer& renderer, Camera& camera)
    : renderer(renderer), camera(camera) {}

SceneObject& Scene::AddObject(std::shared_ptr<Mesh> mesh)
{
    objects.push_back(std::make_unique<SceneObject>(std::move(mesh)));
    return *objects.back();
}

SceneObject& Scene::AddObject(std::unique_ptr<SceneObject> object)
{
    objects.push_back(std::move(object));
    return *objects.back();
}

std::vector<std::unique_ptr<SceneObject>>& Scene::GetObjects()
{
	return objects;
}

void Scene::Update(float deltaTime)
{
    for (auto& obj : objects)
    {
        if (gravityEnabled)
        {
            obj->physics.Accelerate(gravity);
        }
        obj->Update(deltaTime);
    }
}

void Scene::Render()
{
    renderer.BeginScene(camera);

    for (auto& obj : objects)
        renderer.Submit(*obj);
}