#include "PhysicalObject.h"
#include <iostream>

void PhysicalObject::ApplyForce(const glm::vec3& force)
{
	// F = ma	=>	a = F / m
	if (immovable) return;
	acceleration += force / mass;
}

void PhysicalObject::Accelerate(const glm::vec3& acceleration)
{
	if (immovable) return;
	this->acceleration += acceleration;
}

void PhysicalObject::Update(float deltaTime)
{
	if (immovable)
	{
		// Не позволяем не-движимым объектам двигаться или накапливать ускорение
		velocity = glm::vec3(0.0f);
		acceleration = glm::vec3(0.0f);
		UpdateModelMatrix();
		return;
	}

	// v = v0 + at	=>	v += at
	velocity += acceleration * deltaTime;

	// x = x0 + vt	=>	x += vt
	position += velocity * deltaTime;

	acceleration = glm::vec3(0.0f);

	UpdateModelMatrix();
}

void PhysicalObject::ApplyAABBScale(const glm::vec3& scale)
{
	localAABB.min *= scale;
	localAABB.max *= scale;
}

// SET
void PhysicalObject::SetAABB(const AABB& aabb) { localAABB = aabb; }

void PhysicalObject::SetPosition(const glm::vec3& pos) { position = pos; }

void PhysicalObject::SetVelocity(const glm::vec3& vel) { velocity = vel; }

void PhysicalObject::SetGravityEnabled(bool enabled) { gravityEnabled = enabled; }

void PhysicalObject::SetImmovable(bool immovable) { this->immovable = immovable; }

void PhysicalObject::SetMass(float m) { mass = m; }

void PhysicalObject::SetElasticity(float elasticity) { this->elasticity = elasticity; }

// GET
const AABB& PhysicalObject::GetLocalAABB() const { return localAABB; }

AABB PhysicalObject::GetWorldAABB() const
{
	return { localAABB.min + position, localAABB.max + position };
}

const glm::mat4& PhysicalObject::GetModelMatrix() const { return modelMatrix; }

const glm::vec3& PhysicalObject::GetPosition() const { return position; }

const glm::vec3& PhysicalObject::GetVelocity() const { return velocity; }

bool PhysicalObject::GetGravityEnabled() const { return gravityEnabled; }

bool PhysicalObject::GetImmovable() const { return immovable; }

float PhysicalObject::GetMass() const { return mass; }

float PhysicalObject::GetElasticity() const { return elasticity; }


void PhysicalObject::UpdateModelMatrix()
{
	modelMatrix = glm::translate(glm::mat4(1.0f), position);
}