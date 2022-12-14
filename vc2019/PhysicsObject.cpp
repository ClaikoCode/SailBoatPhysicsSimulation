#include "Includes/PhysicsObject.h"
#include "Includes/NaturalConstants.h"

constexpr float DEFAULT_MASS = 1.0f;
constexpr float DEFAULT_MOI = 1.0f;
constexpr bool DEFAULT_GRAVITY_MODE = true;
static constexpr vec3 ZERO_VEC = vec3(0.0f);

PhysicsObject::PhysicsObject()
	: PhysicsObject(Transform(), ZERO_VEC, ZERO_VEC) {}

PhysicsObject::PhysicsObject(const Transform& transform)	
	: PhysicsObject(transform, ZERO_VEC, ZERO_VEC) {}

PhysicsObject::PhysicsObject(const float mass, const float momentOfInertia)
	: PhysicsObject(Transform(), ZERO_VEC, ZERO_VEC, mass, momentOfInertia) {}

PhysicsObject::PhysicsObject(const vec3 velocity, const vec3 angularVelocity)
	: PhysicsObject(Transform(), velocity, angularVelocity) {}

PhysicsObject::PhysicsObject(const Transform& transform, const vec3 velocity, const vec3 angularVelocity) 
	: PhysicsObject(transform, velocity, angularVelocity, DEFAULT_MASS, DEFAULT_MOI) {}

// Master delegation constructor.
PhysicsObject::PhysicsObject(const Transform& transform, const vec3 velocity, const vec3 angularVelocity, const float mass, const float momentOfInertia) 
	: GameObject(transform),
	m_Velocity(velocity),
	m_AngularVelocity(angularVelocity),
	m_Mass(mass),
	m_MomentOfInertia(momentOfInertia),
	m_Parent(nullptr),
	m_TotalAddedForce(0.0f),
	m_TotalAddedTorque(0.0f),
	m_GravityEnabled(DEFAULT_GRAVITY_MODE) {}

void PhysicsObject::PhysicsUpdate(const float deltaTime)
{
	DefaultPhysicsUpdate(deltaTime);
}

void PhysicsObject::AddForce(const vec3 force)
{
	m_TotalAddedForce += force;
}

void PhysicsObject::AddForceAtPosition(const vec3& force, const vec3& position)
{
	AddForce(force);

	// Gets position vector relative objects global center of mass.
	const vec3 CMRelativePos = position - this->m_Transform.GetGlobalPosition();
	const vec3 torque = glm::cross(CMRelativePos, force);
	AddTorque(torque);
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

void PhysicsObject::EnableGravity() { m_GravityEnabled = true; }
void PhysicsObject::DisableGravity() { m_GravityEnabled = false; }

void PhysicsObject::DefaultPhysicsUpdate(const float deltaTime)
{
	if (m_IsStatic == false)
	{
		if (m_GravityEnabled)
			AddForce(NaturalConstants::gravity * m_Mass); // F = m * g

		m_Velocity += (m_TotalAddedForce / m_Mass) * deltaTime; // F_tot = m * a
		m_AngularVelocity += (m_TotalAddedTorque / m_MomentOfInertia) * deltaTime; // T = I * alpha

		m_Transform.UpdateLocalPosition(m_Velocity * deltaTime);
		m_Transform.UpdateLocalRotation(m_AngularVelocity * deltaTime);
	}

	ResetTotalForceAndTorque();
}
