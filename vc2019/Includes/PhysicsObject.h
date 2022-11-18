#pragma once
#include "Includes/CinderEssentials.h"

#include "Includes/GameObject.h"

class PhysicsObject : public GameObject
{
public:
	PhysicsObject();
	PhysicsObject(const Transform transform);
	PhysicsObject(const vec3 velocity, const vec3 angularVelocity);
	PhysicsObject(const Transform transform, const vec3 velocity, const vec3 angularVelocity);

	~PhysicsObject() = default;

	virtual void Update() override;
	virtual void Draw() override;

public:
	vec3 m_Velocity;
	vec3 m_AngularVelocity;

};