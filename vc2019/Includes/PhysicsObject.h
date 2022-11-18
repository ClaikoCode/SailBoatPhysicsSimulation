#pragma once
#include <vector>

#include "Includes/CinderEssentials.h"

#include "Includes/GameObject.h"


class PhysicsObject : public GameObject
{
public:
	PhysicsObject();
	PhysicsObject(const Transform transform);
	PhysicsObject(const vec3 velocity, const vec3 angularVelocity);
	PhysicsObject(const Transform transform, const vec3 velocity, const vec3 angularVelocity);
	PhysicsObject(const Transform transform, const vec3 velocity, const vec3 angularVelocity, const float mass, const float momentOfInertia);

	~PhysicsObject() = default;

	virtual void Update() override;
	virtual void PhysicsUpdate(const float deltaTime);
	virtual void Draw() override;

	void ApplyForce(const vec3 totalForce, const float deltaTime);
	void ApplyForces(const std::vector<vec3>& forces, const float deltaTime);

private:
	void DefaultInit();

protected:
	vec3 m_Velocity;
	vec3 m_AngularVelocity;

	float m_Mass;
	float m_MomentOfInertia;
};