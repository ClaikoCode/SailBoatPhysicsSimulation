#include "Includes/PhysicsObject.h"



PhysicsObject::PhysicsObject() : GameObject()
{
	m_Velocity = vec3(0.0f);
	m_AngularVelocity = vec3(0.0f);
}

PhysicsObject::PhysicsObject(const Transform transform)	
	: GameObject(transform)
{
	m_Velocity = vec3(0.0f);
	m_AngularVelocity = vec3(0.0f);
}

PhysicsObject::PhysicsObject(const vec3 velocity, const vec3 angularVelocity) 
	: GameObject()
{
	m_Velocity = velocity;
	m_AngularVelocity = angularVelocity;
}

PhysicsObject::PhysicsObject(const Transform transform, const vec3 velocity, const vec3 angularVelocity) 
	: GameObject(transform)
{
	m_Velocity = velocity;
	m_AngularVelocity = angularVelocity;
}
