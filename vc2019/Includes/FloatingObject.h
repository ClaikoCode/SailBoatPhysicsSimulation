#pragma once

#include "Includes/GameObject.h"
#include "Includes/PhysicsObject.h"

// A floater is assumed to be a box of a certain width. 
class FloatingObject : public GameObject
{
public:
	FloatingObject();
	FloatingObject(const float boxSize);

	~FloatingObject() = default;

	void Draw() override;
	void Update() override;

	float CalculateSubmergedVolume(const float globalSeaHeight) const;
	vec3 CalculateBuoyancyForce(const float globalSeaHeight) const;

	void AttachToObject(const PhysicsObject& object);

private:
	void InitFloaterMesh();
	float GetTotalVolume() const;

private:
	float m_BoxSize;
};