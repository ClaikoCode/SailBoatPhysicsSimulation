#include "Includes/FloatingObject.h"

// TODO: Remove at "release"
// ---- DEBUG VARIABLES  ----
constexpr bool _SCALE_WITH_SIZE = false; // Make rendered object proportional to the box size.

FloatingObject::FloatingObject()
	: GameObject()
{
	DefaultInit();
}

FloatingObject::FloatingObject(const float boxSize)
	: GameObject()
{
	DefaultInit();

	m_BoxSize = boxSize;

	if(_SCALE_WITH_SIZE)
		m_Transform.UpdateLocalScale(m_BoxSize); 
}

void FloatingObject::Draw()
{
	DefaultDraw();
}

void FloatingObject::Update()
{

}

float FloatingObject::CalculateSubmergedVolume(const float globalSeaHeight) const
{
	float currentHeight = m_Transform.GetGlobalPosition().y;
	// Positive if sea height is over current height and negative otherwise.
	float heightDiff = globalSeaHeight - currentHeight;

	float halfBox = m_BoxSize / 2.0f;
	float minVal = -halfBox;
	float maxVal = halfBox;

	// Gets a value between 0 and 1 based on how much of the box is under the water.
	// 1 would mean that the whole box is under water and 0 means that no part of the box is under water.
	float inverseLerp = (heightDiff - minVal) / (maxVal - minVal);
	float submergedVolume = glm::clamp(inverseLerp, 0.0f, 1.0f);

	return submergedVolume * GetTotalVolume();
}

void FloatingObject::AttachToObject(const PhysicsObject& object)
{
	m_Transform.SetParentTransform(object.m_Transform);
	m_AttachedObject = &object;
}

void FloatingObject::DefaultInit()
{
	m_BoxSize = 1.0f;
	SetMesh(geom::Cube());
	m_AttachedObject = nullptr;
}

float FloatingObject::GetTotalVolume() const
{
	return m_BoxSize * m_BoxSize * m_BoxSize;
}
