#include "Includes/FloatingObject.h"
#include "Includes/MathHelpers.h"
#include "Includes/NaturalConstants.h"

constexpr float DEFAULT_BOX_SIZE = 0.5f;

// TODO: Remove at "release"
// ---- DEBUG VARIABLES  ----
constexpr bool _SCALE_WITH_SIZE = true; // Make rendered object proportional to the box size.

FloatingObject::FloatingObject()
	: FloatingObject(DEFAULT_BOX_SIZE) {}

FloatingObject::FloatingObject(const float boxSize)
	: m_BoxSize(boxSize)
{
	InitFloaterMesh();	
}

void FloatingObject::Draw()
{
	DefaultDraw();
}

void FloatingObject::Update() {}

float FloatingObject::CalculateSubmergedVolume(const float globalSeaHeight) const
{
	float currentCMHeight = m_Transform.GetGlobalPosition().y;
	// Positive if sea height is over current height and negative otherwise.
	float heightDiff = globalSeaHeight - currentCMHeight;

	float halfBox = m_BoxSize / 2.0f;
	float minVal = -halfBox;
	float maxVal = halfBox;

	// Gets a value between 0 and 1 based on how much of the box is under the water.
	// 1 would mean that the whole box is under water and 0 means that no part of the box is under water.
	float submergedVolume = MathHelpers::InverseLerp(heightDiff, minVal, maxVal);

	return submergedVolume * GetTotalVolume();
}

vec3 FloatingObject::CalculateBuoyancyForce(const float globalSeaHeight) const
{
	const float submergedVolume = CalculateSubmergedVolume(globalSeaHeight);
	const float buoyancyForce = submergedVolume * NaturalConstants::DENSITY_WATER * NaturalConstants::GRAVITATIONAL_CONSTANT; // V * rho * g
	return buoyancyForce * -glm::normalize(NaturalConstants::gravity); // Goes opposite the direction of gravity.
}

void FloatingObject::AttachToObject(const PhysicsObject& object)
{
	m_Transform.SetParentTransform(object.m_Transform);
}

void FloatingObject::InitFloaterMesh()
{
	geom::Cube floaterMesh = geom::Cube();
	if (_SCALE_WITH_SIZE)
		floaterMesh.size(vec3(m_BoxSize));

	SetMesh(floaterMesh);
}

float FloatingObject::GetTotalVolume() const
{
	return m_BoxSize * m_BoxSize * m_BoxSize;
}
