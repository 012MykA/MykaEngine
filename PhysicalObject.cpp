#include "PhysicalObject.h"
#include <iostream>

PhysicalObject::PhysicalObject() : position(glm::vec3(0.0f)), velocity(glm::vec3(0.0f)), acceleration(glm::vec3(0.0f)), mass(1.0f), modelMatrix(glm::mat4(1.0f)) {}

void PhysicalObject::ApplyForce(const glm::vec3& force)
{
	// F = ma	=>	a = F / m
	acceleration += force / mass;
}

void PhysicalObject::Accelerate(const glm::vec3& acceleration)
{
	this->acceleration += acceleration;
}

void PhysicalObject::Update(float deltaTime)
{
	// v = v0 + at	=>	v += at
	velocity += acceleration * deltaTime;

	// x = x0 + vt	=>	x += vt
	position += velocity * deltaTime;

	//acceleration = glm::vec3(0.0f);

	UpdateModelMatrix();
}

// SET
void PhysicalObject::SetPosition(const glm::vec3& pos) { position = pos; }

void PhysicalObject::SetVelocity(const glm::vec3& vel) { velocity = vel; }

void PhysicalObject::SetMass(float m) { mass = m; }

// GET
const glm::mat4& PhysicalObject::GetModelMatrix() const { return modelMatrix; }

const glm::vec3& PhysicalObject::GetPosition() const { return position; }

const glm::vec3& PhysicalObject::GetVelocity() const { return velocity; }

float PhysicalObject::GetMass() const { return mass; }


void PhysicalObject::UpdateModelMatrix()
{
	modelMatrix = glm::translate(glm::mat4(1.0f), position);
}