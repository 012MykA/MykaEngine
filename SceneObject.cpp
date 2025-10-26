#include "SceneObject.h"

SceneObject::SceneObject(std::shared_ptr<Mesh> mesh)
    : name("Object"), mesh(std::move(mesh)), physics() { }

void SceneObject::Update(float deltaTime)
{
    physics.Update(deltaTime);
}

void SceneObject::Draw(Shader& shader, const glm::mat4& viewProjection)
{
    mesh->Draw(shader, physics.GetModelMatrix(), viewProjection);
}

void SceneObject::SetName(const std::string& name) { this->name = name; }

void SceneObject::SetMesh(std::shared_ptr<Mesh> newMesh)
{
	mesh.swap(newMesh);
}

const glm::mat4& SceneObject::GetModelMatrix() const { return physics.GetModelMatrix(); }

std::shared_ptr<Mesh> SceneObject::GetMesh() const { return mesh; }

std::string& SceneObject::GetName() { return name; }