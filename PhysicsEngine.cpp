#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() {}

void PhysicsEngine::Update(float deltaTime)
{
	for (auto& obj : physicalObjects)
	{
		if (globalGravityEnabled && obj->GetGravityEnabled())
		{
			obj->Accelerate(globalGravity);
		}

		obj->Update(deltaTime);
	}

	size_t count = physicalObjects.size();
	for (size_t i = 0; i < count; ++i)
	{
		PhysicalObject* objA = physicalObjects[i];
		AABB aabbA = objA->GetWorldAABB();

		for (size_t j = i + 1; j < count; ++j)
		{
			PhysicalObject* objB = physicalObjects[j];
			AABB aabbB = objB->GetWorldAABB();

			// Handle Collision
			if (AABB_vs_AABB(aabbA, aabbB))
			{
				HandleCollision(objA, objB);
			}
		}
	}
}

void PhysicsEngine::AddObject(PhysicalObject* object)
{
	physicalObjects.push_back(object);
}

bool PhysicsEngine::AABB_vs_AABB(const AABB& a, const AABB& b) const
{
	bool collisionX = a.max.x >= b.min.x && a.min.x <= b.max.x;
	
	bool collisionY = a.max.y >= b.min.y && a.min.y <= b.max.y;
	
	bool collisionZ = a.max.z >= b.min.z && a.min.z <= b.max.z;

	return collisionX && collisionY && collisionZ;
}

void PhysicsEngine::HandleCollision(PhysicalObject* objA, PhysicalObject* objB)
{
    AABB a = objA->GetWorldAABB();
    AABB b = objB->GetWorldAABB();

    float dx = std::min(a.max.x - b.min.x, b.max.x - a.min.x);
    float dy = std::min(a.max.y - b.min.y, b.max.y - a.min.y);
    float dz = std::min(a.max.z - b.min.z, b.max.z - a.min.z);

    glm::vec3 mtv = glm::vec3(0.0f);
    if (dx < dy && dx < dz)
    {
        float signX = objA->GetPosition().x < objB->GetPosition().x ? -1.0f : 1.0f;
        mtv.x = signX * dx;
    }
    else if (dy < dx && dy < dz)
    {
        float signY = objA->GetPosition().y < objB->GetPosition().y ? -1.0f : 1.0f;
        mtv.y = signY * dy;
    }
    else
    {
        float signZ = objA->GetPosition().z < objB->GetPosition().z ? -1.0f : 1.0f;
        mtv.z = signZ * dz;
    }

    objA->SetPosition(objA->GetPosition() + mtv * 0.5f);
    objB->SetPosition(objB->GetPosition() - mtv * 0.5f);

	// Update positions
    objA->Update(0.0f);
    objB->Update(0.0f);

	// m1v1 + m2v2 = m1v1' + m2v2'
	float m1 = objA->GetMass();
	float m2 = objB->GetMass();

	glm::vec3 v1 = objA->GetVelocity();
	glm::vec3 v2 = objB->GetVelocity();

	glm::vec3 v1Final = (v1 * (m1 - m2) + 2.0f * m2 * v2) / (m1 + m2);
	glm::vec3 v2Final = (v2 * (m2 - m1) + 2.0f * m1 * v1) / (m1 + m2);

	objA->SetVelocity(v1Final);
	objB->SetVelocity(v2Final);
}