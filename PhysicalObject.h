#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct AABB
{
	glm::vec3 min;
	glm::vec3 max;
};

class PhysicalObject
{
public:
	PhysicalObject() = default;

	void ApplyForce(const glm::vec3& force);
	void Accelerate(const glm::vec3& acceleration);

	void Update(float deltaTime);

	friend class ImGuiManager;

public:
	// Set
	void SetAABB(const AABB& aabb);

	void SetPosition(const glm::vec3& pos);
	void SetVelocity(const glm::vec3& vel);
	void SetGravityEnabled(bool enabled);
	void SetMass(float m);

	// Get
	const AABB& GetLocalAABB() const;
	AABB GetWorldAABB() const;

	const glm::mat4& GetModelMatrix() const;
	const glm::vec3& GetPosition() const;
	const glm::vec3& GetVelocity() const;
	bool GetGravityEnabled() const;
	float GetMass() const;

private:
	// --- Collision ---
	AABB localAABB = { glm::vec3(-0.5f), glm::vec3(0.5f) };

	// --- Kinematics ---
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 velocity = glm::vec3(0.0f);
	glm::vec3 acceleration = glm::vec3(0.0f);

	// --- Gravity ---
	bool gravityEnabled = true;

	// --- Properties ---
	float mass = 1.0f;

	// --- Matrix ---
	glm::mat4 modelMatrix = glm::mat4(1.0f);

private:
	void UpdateModelMatrix();
};