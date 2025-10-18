#include "SceneObject.h"

SceneObject::SceneObject(std::shared_ptr<Mesh> mesh)
    : mesh(std::move(mesh)), physics() {}

void SceneObject::Update(float deltaTime)
{
    physics.Update(deltaTime);
}

void SceneObject::Draw(Shader& shader, const glm::mat4& viewProjection)
{
    mesh->Draw(shader, physics.GetModelMatrix(), viewProjection);
}

const glm::mat4& SceneObject::GetModelMatrix() const { return physics.GetModelMatrix(); }

std::shared_ptr<Mesh> SceneObject::GetMesh() const { return mesh; }
