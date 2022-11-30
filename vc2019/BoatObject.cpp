#include "Includes/BoatObject.h"
#include "Includes/NaturalConstants.h"

#include "cinder/Log.h"

constexpr float DEFAULT_WIDTH = 24.0f;
constexpr float DEFAULT_DEPTH = 40.0f;
constexpr float DEFAULT_HEIGHT = 6.0f;
constexpr float DEFAULT_MASS = 10.0f;

constexpr vec3 DEFAULT_BOAT_COLOR = vec3(107.0f, 69.0f, 54.0f) / 255.0f;

// ---- DEBUG VARIABLES ----
constexpr float _MoI_SCALING = 20.0f;
constexpr float _MASS_SCALING = 2.5f;

BoatObject::BoatObject()
{
	DefaultInit();
}

BoatObject::BoatObject(const BoatObject& other) 
	: PhysicsObject(other)
{
	DefaultCopy(other);
}

BoatObject& BoatObject::operator=(const BoatObject& other)
{
	PhysicsObject::operator=(other);

	DefaultCopy(other);

	return *this;
}

void BoatObject::Draw()
{
	for (FloatingObject& floater : m_Floaters)
	{
		floater.Draw();
	}

	m_SailObject.Draw();

	DefaultDraw();
}

void BoatObject::Update()
{
	m_SailObject.Update();
}

void BoatObject::PhysicsUpdate(const float deltaTime)
{
	for (const FloatingObject& floater : m_Floaters)
	{
		float globalHeightLevel = 0.0f;
		if (m_WaveManager)
		{
			vec3 globalPos = floater.m_Transform.GetGlobalPosition();
			globalHeightLevel = m_WaveManager->CalculateWaveHeight(globalPos.x, globalPos.z);
		}

		float submergedVolume = floater.CalculateSubmergedVolume(globalHeightLevel);
		float buoyancyForce = submergedVolume * NaturalConstants::DENSITY_WATER * NaturalConstants::GRAVITATIONAL_CONSTANT; // V * rho * g
		vec3 buoyancyForceVec = buoyancyForce * -glm::normalize(NaturalConstants::gravity); // Goes opposite the direction of gravity.

		AddForceAtPosition(buoyancyForceVec, GetRelativeFloaterPos(floater));
	}

	DefaultPhysicsUpdate(deltaTime);
}

void BoatObject::AttachWaveManager(WaveManager& waveManager)
{
	m_WaveManager = &waveManager;
	
	// TODO: Add so that global position can be set.
	//const vec3 currentPos = m_Transform.GetGlobalPosition();
	//float waterHeight = m_WaveManager->CalculateWaveHeight(currentPos.x, currentPos.z);
}

void BoatObject::DetachWaveManager()
{
	m_WaveManager = nullptr;
}

void BoatObject::DefaultInit()
{
	geom::Cube boatBody = geom::Cube().size(vec3(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_DEPTH));
	SetMesh(boatBody);
	m_BoatDimensions = BoatDimensions({ DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_DEPTH });

	m_Mass = _MASS_SCALING * DEFAULT_MASS;
	m_MomentOfInertia = CalculateMomentOfInertia(m_BoatDimensions.m_BoatWidth, m_BoatDimensions.m_BoatDepth);
	
	InitSail(); // Has to happen after defining boat dimensions.

	InitFloaters();
	SetMeshColor(DEFAULT_BOAT_COLOR);

	m_WaveManager = nullptr;
}

void BoatObject::InitSail()
{
	m_SailObject = SailObject();
	m_SailObject.m_Transform.SetParentTransform(m_Transform);

	const float sailOffset = m_SailObject.GetSailHeight() / 2.0f + m_BoatDimensions.m_BoatHeight / 2.0f;
	const float airGap = 2.0f; // Air gap between hull and sail (just for visuals).
	m_SailObject.m_Transform.SetLocalPosition(0.0f, sailOffset + airGap, 0.0f);
}

void BoatObject::InitFloaters()
{
	m_Floaters = {};
	const float floaterSize = 0.4f;
	FloatingObject floater = FloatingObject(floaterSize);

	floater.AttachToObject(*this);
	floater.m_IsDrawable = true;

	float halfBoatLength = DEFAULT_WIDTH / 2.0f;
	float halfBoatBreadth = DEFAULT_DEPTH / 2.0f;
	
	vec3 floaterPos = vec3(halfBoatLength, 0.0f, halfBoatBreadth);
	AddFloaterPair(floater, floaterPos);

	floaterPos.x = -floaterPos.x;
	AddFloaterPair(floater, floaterPos);

	floaterPos = vec3(0.0f, 0.0f, halfBoatBreadth);
	AddFloaterPair(floater, floaterPos);

	floaterPos = vec3(halfBoatLength, 0.0f, 0.0f);
	AddFloaterPair(floater, floaterPos);
}

void BoatObject::DefaultCopy(const BoatObject& other)
{
	m_Floaters = other.m_Floaters;
	m_WaveManager = other.m_WaveManager;

	// Copy sail values and set this transform as new parent.
	m_SailObject = other.m_SailObject;
	m_SailObject.m_Transform.SetParentTransform(this->m_Transform);

	// Re-attach all floaters to this object instead of other.
	for (FloatingObject& floater : m_Floaters)
	{
		floater.AttachToObject(*this);
	}

	m_BoatDimensions = other.m_BoatDimensions;
}

void BoatObject::AddFloaterPair(const FloatingObject& floater, const vec3& position)
{
	m_Floaters.push_back(floater);
	m_Floaters.back().m_Transform.SetLocalPosition(position);

	m_Floaters.push_back(floater);
	m_Floaters.back().m_Transform.SetLocalPosition(-position);
}

float BoatObject::CalculateMomentOfInertia(const float l, const float b) const
{
	// Boat typical MoI: (m / 48) * (4 * l^2 + 3 * b^2)
	float boatTypicalMoI = (m_Mass / 48.0f) * (4.0f * glm::pow(l, 2.0f) + 3.0f * glm::pow(b, 2.0f));

	return _MoI_SCALING * boatTypicalMoI;
}

cinder::vec3 BoatObject::GetRelativeFloaterPos(const FloatingObject& floater) const
{
	vec3 currentRot = m_Transform.GetLocalRotation();
	mat4 rotMatrix = glm::eulerAngleXYZ(currentRot.x, currentRot.y, currentRot.z);
	vec3 rotatedPos = rotMatrix * vec4(floater.m_Transform.GetLocalPosition(), 0.0f);

	return rotatedPos;
}

