#pragma once

#include <vector>

#include "Includes/PhysicsObject.h"
#include "Includes/FloatingObject.h"
#include "Includes/WaveManager.h"
#include "Includes/SailObject.h"
#include "Includes/KeelObject.h"

class BoatObject : public PhysicsObject
{
private:
	struct BoatDimensions
	{
		float m_BoatLength;
		float m_BoatHeight;
		float m_BoatBreadth;
	};

public:
	BoatObject();
	BoatObject(const float width, const float depth);
	~BoatObject() = default;

	BoatObject(const BoatObject& other);
	BoatObject& operator=(const BoatObject& other);
	
	void Draw() override;
	void Update() override;
	void PhysicsUpdate(const float deltaTime) override;

	void AttachWaveManager(const WaveManager& waveManager);
	void DetachWaveManager();

private:
	void InitBoatBody();
	void InitSail();
	void InitFloaters();
	void OuterRimFloaterInit(const FloatingObject& baseFloater);
	void VolumetricFloaterInit();

	void DefaultCopy(const BoatObject& other);

	float CalculateMomentOfInertia(const float l, const float b) const;

	void AddFloaterPair(const FloatingObject& floater, const vec3& position);
	vec3 GetFloaterPosRelativeBoat(const FloatingObject& floater) const;

	vec3 CalculateLiftForce(const vec3 windDirection) const;

private:
	std::vector<FloatingObject> m_Floaters;
	const WaveManager* m_WaveManager;

	SailObject m_SailObject;
	KeelObject m_KeelObject;

	BoatObject::BoatDimensions m_BoatDimensions;
};