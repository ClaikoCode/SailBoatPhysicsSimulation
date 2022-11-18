#include "Includes/PhysicsObject.h"



PhysicsObject::PhysicsObject() 
	: GameObject()
{
	DefaultInit();
}

PhysicsObject::PhysicsObject(const Transform transform)	
	: GameObject(transform)
{
	DefaultInit();
}

PhysicsObject::PhysicsObject(const vec3 velocity, const vec3 angularVelocity) 
	: GameObject()
{
	DefaultInit();

	m_Velocity = velocity;
	m_AngularVelocity = angularVelocity;
}

PhysicsObject::PhysicsObject(const Transform transform, const vec3 velocity, const vec3 angularVelocity) 
	: GameObject(transform)
{
	DefaultInit();

	m_Velocity = velocity;
	m_AngularVelocity = angularVelocity;
}

PhysicsObject::PhysicsObject(
	const Transform transform, 
	const vec3 velocity, 
	const vec3 angularVelocity, 
	const float mass, 
	const float momentOfInertia 
) 
	: GameObject(transform)
{
	m_Velocity = velocity;
	m_AngularVelocity = angularVelocity;
	m_Mass = mass;
	m_MomentOfInertia = momentOfInertia;
}

void PhysicsObject::Update()
{
	
}

void PhysicsObject::PhysicsUpdate(const float deltaTime)
{
	m_Transform.UpdatePosition(m_Velocity * deltaTime);
	m_Transform.UpdateRotation(m_AngularVelocity * deltaTime);
}

void PhysicsObject::Draw()
{

}

void PhysicsObject::ApplyForce(const vec3 totalForce, const float deltaTime)
{
	vec3 acceleration = totalForce / m_Mass;
	m_Velocity += acceleration * deltaTime;
}

void PhysicsObject::ApplyForces(const std::vector<vec3>& forces, const float deltaTime)
{
	vec3 totalForce = vec3(0.0f);
	for (const vec3& force : forces)
		totalForce += force;

	ApplyForce(totalForce, deltaTime);
}

void PhysicsObject::DefaultInit()
{
	m_Velocity = vec3(0.0f);
	m_AngularVelocity = vec3(0.0f);

	m_Mass = 1.0f;
	m_MomentOfInertia = 1.0f;
}
