#pragma once
#include <vector>
#include <memory.h>

#include "Includes/CinderEssentials.h"

#include "Includes/GameObject.h"


class PhysicsObject : public GameObject
{
public:
	PhysicsObject();
	PhysicsObject(const Transform transform);
	PhysicsObject(const float mass, const float momentOfInertia);
	PhysicsObject(const vec3 velocity, const vec3 angularVelocity);
	PhysicsObject(const Transform transform, const vec3 velocity, const vec3 angularVelocity);
	PhysicsObject(const Transform transform, const vec3 velocity, const vec3 angularVelocity, const float mass, const float momentOfInertia);

	~PhysicsObject() = default;

	virtual void Update() override;
	virtual void PhysicsUpdate(const float deltaTime);
	virtual void Draw() override;

	void AddForce(const vec3 force);
	void AddForceAtPosition(const vec3 force, const vec3 position);
	void AddForces(const std::vector<vec3>& forces);

	void AddTorque(const vec3 torque);
	void AddTorques(const std::vector<vec3>& torques);

	void ResetTotalForceAndTorque();

private:
	void DefaultInit();



public:
	vec3 m_Velocity;
	vec3 m_AngularVelocity;

	float m_Mass;
	float m_MomentOfInertia;

	bool m_IsStatic;

	PhysicsObject* m_Parent;

private:
	vec3 m_TotalAddedForce;
	vec3 m_TotalAddedTorque;
	
};