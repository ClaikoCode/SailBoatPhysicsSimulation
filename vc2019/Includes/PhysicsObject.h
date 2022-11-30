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
	PhysicsObject(const Transform& transform, const vec3 velocity, const vec3 angularVelocity, const float mass, const float momentOfInertia);

	~PhysicsObject() = default;

	virtual void Draw() override;
	virtual void Update() override;
	virtual void PhysicsUpdate(const float deltaTime);

	void AddForce(const vec3 force);
	// Position is relative to the object position.
	void AddForceAtPosition(const vec3& force, const vec3& position);
	void AddForces(const std::vector<vec3>& forces);

	void AddTorque(const vec3 torque);
	void AddTorques(const std::vector<vec3>& torques);

	void EnableGravity();
	void DisableGravity();

protected:
	// Should always be run as the last function in physics update function.
	void DefaultPhysicsUpdate(const float deltaTime);

	void ResetTotalForceAndTorque();

	void ApplyDrag();

public:
	vec3 m_Velocity;
	// Velocity of euler angles in radians / second.
	vec3 m_AngularVelocity;

	float m_Mass;
	float m_MomentOfInertia;

	PhysicsObject* m_Parent;

private:
	vec3 m_TotalAddedForce;
	vec3 m_TotalAddedTorque;
	
	bool m_GravityEnabled;
};