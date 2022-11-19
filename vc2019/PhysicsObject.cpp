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

PhysicsObject::PhysicsObject(const float mass, const float momentOfInertia) 
	: GameObject()
{
	DefaultInit();

	m_Mass = mass;
	m_MomentOfInertia = momentOfInertia;
}

void PhysicsObject::Update()
{
	
}

void PhysicsObject::PhysicsUpdate(const float deltaTime)
{
	if (m_IsStatic == false) 
	{
		m_Velocity += (m_TotalAddedForce / m_Mass) * deltaTime; // F = m * a
		m_AngularVelocity += (m_TotalAddedTorque / m_MomentOfInertia) * deltaTime; // T = I * alpha

		m_Transform.UpdateLocalPosition(m_Velocity * deltaTime);
		m_Transform.UpdateLocalRotation(m_AngularVelocity * deltaTime);
	}

	ResetTotalForceAndTorque();
}

void PhysicsObject::Draw()
{
	gl::ScopedModelMatrix model;
	gl::multModelMatrix(m_Transform.GetTransformMatrix());
	gl::ScopedColor color( Colorf(CM_RGB, vec3(1.0f)) );
	m_Mesh->draw();
}

void PhysicsObject::AddForce(const vec3 force)
{
	m_TotalAddedForce += force;
}

void PhysicsObject::AddForceAtPosition(const vec3 force, const vec3 position)
{
	AddForce(force);

	vec3 centerOfMassToPos = position - m_Transform.GetGlobalPosition();
	m_TotalAddedTorque += glm::cross(centerOfMassToPos, force);
}

void PhysicsObject::AddForces(const std::vector<vec3>& forces)
{
	for (const vec3& force : forces)
		AddForce(force);
}

void PhysicsObject::AddTorque(const vec3 torque)
{
	m_TotalAddedTorque += torque;
}

void PhysicsObject::AddTorques(const std::vector<vec3>& torques)
{
	for (const vec3& torque : torques)
		AddTorque(torque);
}

void PhysicsObject::ResetTotalForceAndTorque()
{
	m_TotalAddedForce = vec3(0.0f);
	m_TotalAddedTorque = vec3(0.0f);
}

void PhysicsObject::DefaultInit()
{
	m_Velocity			= vec3(0.0f);
	m_AngularVelocity	= vec3(0.0f);
	m_TotalAddedForce	= vec3(0.0f);
	m_TotalAddedTorque	= vec3(0.0f);

	m_Mass = 1.0f;
	m_MomentOfInertia = 1.0f;

	m_IsStatic = false;
	m_Parent = nullptr;
}
