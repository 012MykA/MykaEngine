#pragma once

#include "PhysicalObject.h"

#include <vector>

class PhysicsEngine
{
public:
	PhysicsEngine();

	void Update(float deltaTime);

	void AddObject(PhysicalObject* object);

	friend class ImGuiManager;

private:
	std::vector<PhysicalObject*> physicalObjects;

	bool AABB_vs_AABB(const AABB& a, const AABB& b) const;
	void HandleCollision(PhysicalObject* objA, PhysicalObject* objB);

	glm::vec3 globalGravity = glm::vec3(0.0f, -9.81f, 0.0f);
	bool globalGravityEnabled = false;
};
