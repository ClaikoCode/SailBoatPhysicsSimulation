#pragma once

#include <vector>

#include "Includes/PhysicsObject.h"
#include "Includes/FloatingObject.h"
#include "Includes/SailObject.h"
#include "Includes/KeelObject.h"

#include "Includes/WaveManager.h"
#include "Includes/WindManager.h"

class BoatObject : public PhysicsObject
{
private:
	// Dimensions for boat length, height and breadth. The purpose is to make references to boat dimensions more readable.
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
	void AttachWindManager(const WindManager& windManager);
	void DetachWaveManager();

private:

	void DefaultCopy(const BoatObject& other);

	void InitBoatBody();
	void InitSail();
	void InitFloaters();
	void OuterRimFloaterInit(const FloatingObject& baseFloater);
	void VolumetricFloaterInit();
	float CalculateMomentOfInertia(const float l, const float b) const;

	void AddFloaterPair(const FloatingObject& floater, const vec3& position);

	// Applies the buoyancy force (and torque) from each floater thats attached to the boat.
	void ApplyFloaterForces();
	// Applies forces that the wind creates.
	void ApplyWindForces();

	vec3 CalculateLiftForce(const vec3 windDirection) const;
	
private:
	std::vector<FloatingObject> m_Floaters;

	const WaveManager* m_WaveManager;
	const WindManager* m_WindManager;

	SailObject m_SailObject;
	KeelObject m_KeelObject;

	BoatObject::BoatDimensions m_BoatDimensions;
};