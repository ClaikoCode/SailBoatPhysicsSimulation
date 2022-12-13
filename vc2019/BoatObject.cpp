#include "Includes/BoatObject.h"
#include "Includes/NaturalConstants.h"
#include "Includes/MathHelpers.h"

#include "cinder/Log.h"

constexpr float DEFAULT_WIDTH = 50.0f;
constexpr float DEFAULT_DEPTH = 70.0f;
constexpr float DEFAULT_HEIGHT = 6.0f;
constexpr float DEFAULT_MASS = 500.0f;

constexpr vec3 DEFAULT_BOAT_COLOR = vec3(107.0f, 69.0f, 54.0f) / 255.0f;

// TODO: Remove when done
#include "Includes/WindManager.h"

// ---- DEBUG VARIABLES ----
constexpr float _MoI_SCALING = 2.0f;
constexpr float _MASS_SCALING = 5.0f;

BoatObject::BoatObject()
	: BoatObject(DEFAULT_WIDTH, DEFAULT_DEPTH) {}


BoatObject::BoatObject(const float width, const float depth)
	: PhysicsObject(_MASS_SCALING* DEFAULT_MASS, 0.0f), // MoI set to 0.0f as it is going to be recalculated last in constructor.
	m_Floaters(),
	m_WaveManager(nullptr),
	m_WindManager(nullptr),
	m_SailObject(),
	m_KeelObject(),
	m_BoatDimensions({ width, DEFAULT_HEIGHT, depth })
{
	InitBoatBody();
	InitSail();
	InitFloaters();

	m_MomentOfInertia = CalculateMomentOfInertia(m_BoatDimensions.m_BoatLength, m_BoatDimensions.m_BoatBreadth);
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
	ApplyFloaterForces();
	DefaultPhysicsUpdate(deltaTime);
}

void BoatObject::AttachWaveManager(const WaveManager& waveManager)
{
	m_WaveManager = &waveManager;
	
	// TODO: Add so that global position can be set.
	// Move boat to wherever water plane is and at a proper wave height.
	//const vec3 currentPos = m_Transform.GetGlobalPosition();
	//float waterHeight = m_WaveManager->CalculateWaveHeight(currentPos.x, currentPos.z);
}

void BoatObject::AttachWindManager(const WindManager& windManager)
{
	m_WindManager = &windManager;
}

void BoatObject::DetachWaveManager()
{
	m_WaveManager = nullptr;
}

void BoatObject::InitBoatBody()
{
	const vec3 sizeVector = vec3(m_BoatDimensions.m_BoatLength, m_BoatDimensions.m_BoatHeight, m_BoatDimensions.m_BoatBreadth);
	geom::Cube boatBody = geom::Cube().size(sizeVector).subdivisions(10);
	SetMesh(boatBody);
	SetMeshColor(DEFAULT_BOAT_COLOR);
}

void BoatObject::InitSail()
{
	m_SailObject.m_Transform.SetParentTransform(this->m_Transform);

	const float sailOffset = m_SailObject.GetSailHeight() / 2.0f + m_BoatDimensions.m_BoatHeight / 2.0f;
	const float airGap = 2.0f; // Air gap between hull and sail (just for visuals).
	m_SailObject.m_Transform.SetLocalPosition(0.0f, sailOffset + airGap, 0.0f);
}

void BoatObject::InitFloaters()
{
	const float floaterSize = 0.6f;
	FloatingObject floater = FloatingObject(floaterSize);

	floater.AttachToObject(*this);
	floater.m_IsDrawable = true;

	//VolumetricFloaterInit();

	OuterRimFloaterInit(floater);
}

void BoatObject::OuterRimFloaterInit(const FloatingObject& baseFloater)
{
	const uint32_t nSideFloaters = 12;
	const uint32_t nFrontBackFloaters = 12;
	const uint32_t nHeightLevels = 7;

	const float sideDelta = m_BoatDimensions.m_BoatLength / (float)nSideFloaters;
	const float frontDelta = m_BoatDimensions.m_BoatBreadth / (float)nFrontBackFloaters;
	const float heightDelta = m_BoatDimensions.m_BoatHeight / (float)nHeightLevels;

	const float halfBoatLength = m_BoatDimensions.m_BoatLength / 2.0f;
	const float halfBoatBreadth = m_BoatDimensions.m_BoatBreadth / 2.0f;
	const float halfBoatHeight = m_BoatDimensions.m_BoatHeight / 2.0f;

	const vec3 sideDeltaVec = vec3(-sideDelta, 0.0f, 0.0f);
	const vec3 frontDeltaVec = vec3(0.0f, 0.0f, -frontDelta);
	const vec3 heightDeltaVec = vec3(0.0f, -heightDelta, 0.0f);

	const vec3 topRightBoatQuadrant = vec3(halfBoatLength, 0.0f, halfBoatBreadth);
	const vec3 bottomOfBoat = vec3(0.0f, halfBoatHeight, 0.0f);


	for (int heightLevel = 0; heightLevel < nHeightLevels + 1; heightLevel++)
	{
		const vec3 heightOffset = bottomOfBoat + heightDeltaVec * (float)heightLevel;

		for (int i = 0; i < nSideFloaters; i++)
		{
			vec3 floaterPos = topRightBoatQuadrant + sideDeltaVec * (float)i + heightOffset;
			AddFloaterPair(baseFloater, floaterPos);
		}

		// Start on one due to floaters already placed in top corner
		for (int i = 1; i < nFrontBackFloaters + 1; i++)
		{
			vec3 floaterPos = topRightBoatQuadrant + frontDeltaVec * (float)i + heightOffset;
			AddFloaterPair(baseFloater, floaterPos);
		}
	}
}

// TODO: Implement well defined function for this.
void BoatObject::VolumetricFloaterInit()
{
	const float floaterSize = m_BoatDimensions.m_BoatHeight;
	FloatingObject floater = FloatingObject(floaterSize);

	int counter = 0;
	float decimalRemainder = FLT_MAX;
	const float decimalLimit = 0.05f;
	while (decimalRemainder > 0.05f)
	{
		float divResult = m_BoatDimensions.m_BoatBreadth / (floaterSize * glm::pow(2.0f, (float)counter));
		decimalRemainder = divResult - glm::floor(divResult);
		counter++;
	}
}

void BoatObject::DefaultCopy(const BoatObject& other)
{
	m_Floaters = other.m_Floaters;
	m_WaveManager = other.m_WaveManager;
	m_WindManager = other.m_WindManager;
	m_BoatDimensions = other.m_BoatDimensions;

	// Copy sail values and set this transform as new parent.
	m_SailObject = other.m_SailObject;
	m_SailObject.m_Transform.SetParentTransform(this->m_Transform);

	m_KeelObject = other.m_KeelObject;
	m_KeelObject.m_Transform.SetParentTransform(this->m_Transform);

	// Re-attach all floaters to this object instead of other.
	for (FloatingObject& floater : m_Floaters)
	{
		floater.AttachToObject(*this);
	}
}

float BoatObject::CalculateMomentOfInertia(const float l, const float b) const
{
	// Boat typical MoI: (m / 48) * (4 * l^2 + 3 * b^2)
	float boatTypicalMoI = (m_Mass / 48.0f) * (4.0f * glm::pow(l, 2.0f) + 3.0f * glm::pow(b, 2.0f));

	return _MoI_SCALING * boatTypicalMoI;
}

void BoatObject::AddFloaterPair(const FloatingObject& floater, const vec3& position)
{
	m_Floaters.push_back(floater);
	m_Floaters.back().m_Transform.SetLocalPosition(position);

	m_Floaters.push_back(floater);
	m_Floaters.back().m_Transform.SetLocalPosition(-position);
}

void BoatObject::ApplyFloaterForces()
{
	for (const FloatingObject& floater : m_Floaters)
	{
		float globalHeightLevel = 0.0f;
		if (m_WaveManager)
		{
			vec3 globalFloaterPos = floater.m_Transform.GetGlobalPosition();
			globalHeightLevel = m_WaveManager->CalculateWaveHeight(globalFloaterPos.x, globalFloaterPos.z);
		}

		const vec3 buoyancyForceVec = floater.CalculateBuoyancyForce(globalHeightLevel);
		AddForceAtPosition(buoyancyForceVec, floater.m_Transform.GetGlobalPosition());
	}
}

void BoatObject::ApplyWindForces()
{
	const vec3 sailGlobalPos = m_SailObject.m_Transform.GetGlobalPosition();
}

glm::vec3 BoatObject::CalculateLiftForce(const vec3 windForce) const
{
	const vec3 globalSailDirection = m_SailObject.GetGlobalSailDirection();
	// This projection gives how much of the wind's force is acted in the direction of the sail.
	return MathHelpers::ProjectVector(windForce, globalSailDirection);
}

