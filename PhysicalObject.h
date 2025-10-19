#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PhysicalObject
{
public:
	PhysicalObject();

	void ApplyForce(const glm::vec3& force);

	void Update(float deltaTime);

	friend class ImGuiManager;
public:
	// Set
	void SetPosition(const glm::vec3& pos);
	void SetVelocity(const glm::vec3& vel);
	void SetMass(float m);

	// Get
	const glm::mat4& GetModelMatrix() const;
	const glm::vec3& GetPosition() const;
	const glm::vec3& GetVelocity() const;
	float GetMass() const;

private:
	// --- Kinematics ---
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	// --- Properties ---
	float mass;

	// --- Matrix ---
	glm::mat4 modelMatrix;

private:
	void UpdateModelMatrix();
};