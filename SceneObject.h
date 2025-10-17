#pragma once

#include "PhysicalObject.h"
#include "Mesh.h"
#include <memory>

class SceneObject
{
public:
    explicit SceneObject(std::shared_ptr<Mesh> mesh);

    SceneObject(const SceneObject&) = delete;
    SceneObject& operator=(const SceneObject&) = delete;
    SceneObject(SceneObject&&) noexcept = default;
    SceneObject& operator=(SceneObject&&) noexcept = default;

    void Update(float deltaTime);
    void Draw(Shader& shader, const glm::mat4& viewProjection);

    const glm::mat4& GetModelMatrix() const;
    std::shared_ptr<Mesh> GetMesh() const;

    PhysicalObject physics;

private:
    std::shared_ptr<Mesh> mesh;
};
