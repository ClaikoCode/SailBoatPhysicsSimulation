#include "Includes/PhysicsObject.h"
#include "Includes/NaturalConstants.h"

constexpr float DEFAULT_MASS = 1.0f;
constexpr float DEFAULT_MoI = 1.0f;
constexpr bool DEFAULT_GRAVITY_MODE = true;

PhysicsObject::PhysicsObject()
	: m_Velocity(0.0f),
	m_AngularVelocity(0.0f),
	m_Mass(DEFAULT_MASS),
	m_MomentOfInertia(DEFAULT_MoI),
	m_Parent(nullptr),
	m_TotalAddedForce(0.0f),
	m_TotalAddedTorque(0.0f),
	m_GravityEnabled(DEFAULT_GRAVITY_MODE) {}

PhysicsObject::PhysicsObject(const Transform transform)	
	: GameObject(transform),
	m_Velocity(0.0f),
	m_AngularVelocity(0.0f),
	m_Mass(DEFAULT_MASS),
	m_MomentOfInertia(DEFAULT_MoI),
	m_Parent(nullptr),
	m_TotalAddedForce(0.0f),
	m_TotalAddedTorque(0.0f),
	m_GravityEnabled(DEFAULT_GRAVITY_MODE) {}

PhysicsObject::PhysicsObject(const vec3 velocity, const vec3 angularVelocity)
	: m_Velocity(velocity),
	m_AngularVelocity(angularVelocity),
	m_Mass(DEFAULT_MASS),
	m_MomentOfInertia(DEFAULT_MoI),
	m_Parent(nullptr),
	m_TotalAddedForce(0.0f),
	m_TotalAddedTorque(0.0f),
	m_GravityEnabled(DEFAULT_GRAVITY_MODE) {}

PhysicsObject::PhysicsObject(const Transform transform, const vec3 velocity, const vec3 angularVelocity) 
	: GameObject(transform),
	m_Velocity(velocity),
	m_AngularVelocity(angularVelocity),
	m_Mass(DEFAULT_MASS),
	m_MomentOfInertia(DEFAULT_MoI),
	m_Parent(nullptr),
	m_TotalAddedForce(0.0f),
	m_TotalAddedTorque(0.0f),
	m_GravityEnabled(DEFAULT_GRAVITY_MODE) {}

PhysicsObject::PhysicsObject(const Transform transform, const vec3 velocity, const vec3 angularVelocity, const float mass, const float momentOfInertia ) 
	: GameObject(transform),
	m_Velocity(velocity),
	m_AngularVelocity(angularVelocity),
	m_Mass(mass),
	m_MomentOfInertia(momentOfInertia),
	m_Parent(nullptr),
	m_TotalAddedForce(0.0f),
	m_TotalAddedTorque(0.0f),
	m_GravityEnabled(DEFAULT_GRAVITY_MODE) {}

PhysicsObject::PhysicsObject(const float mass, const float momentOfInertia) 
	: GameObject()
{

	m_Mass = mass;
	m_MomentOfInertia = momentOfInertia;
}

void PhysicsObject::Update()
{
	
}

void PhysicsObject::PhysicsUpdate(const float deltaTime)
{
	DefaultPhysicsUpdate(deltaTime);
}

void PhysicsObject::Draw()
{
	DefaultDraw();
}

void PhysicsObject::AddForce(const vec3 force)
{
	m_TotalAddedForce += force;
}

void PhysicsObject::AddForceAtPosition(const vec3& force, const vec3& position)
{
	AddForce(force);
	m_TotalAddedTorque += glm::cross(position, force);
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
