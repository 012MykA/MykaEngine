#pragma once

#include "PhysicalObject.h"
#include "Mesh.h"
#include <memory>

class SceneObject
{
public:
	// Main constructor
    explicit SceneObject(std::shared_ptr<Mesh> mesh);

    void Update(float deltaTime);
    void Draw(Shader& shader, const glm::mat4& viewProjection);

public:
	void SetName(const std::string& name);
    void SetMesh(std::shared_ptr<Mesh> newMesh);

    const glm::mat4& GetModelMatrix() const;
    std::shared_ptr<Mesh> GetMesh() const;
    std::string& GetName();

    PhysicalObject physics;

private:
	std::string name;
    std::shared_ptr<Mesh> mesh;

public:
	// Disable copying
    SceneObject(const SceneObject&) = delete;
    SceneObject(SceneObject&&) noexcept = default;

	// Disable assignment
    SceneObject& operator=(const SceneObject&) = delete;
    SceneObject& operator=(SceneObject&&) noexcept = default;
};
