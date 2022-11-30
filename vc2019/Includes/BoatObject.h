#pragma once

#include <vector>

#include "Includes/PhysicsObject.h"
#include "Includes/FloatingObject.h"
#include "Includes/WaveManager.h"
#include "Includes/SailObject.h"

class BoatObject : public PhysicsObject
{
private:
	struct BoatDimensions
	{
		float m_BoatWidth;
		float m_BoatHeight;
		float m_BoatDepth;
	};

public:
	BoatObject();
	BoatObject(const BoatObject& other);
	BoatObject& operator=(const BoatObject& other);
	~BoatObject() = default;

	virtual void Draw() override;
	virtual void Update() override;
	virtual void PhysicsUpdate(const float deltaTime) override;

	void AttachWaveManager(WaveManager& waveManager);
	void DetachWaveManager();

private:
	void DefaultInit();
	void InitSail();
	void InitFloaters();

	void DefaultCopy(const BoatObject& other);

	void AddFloaterPair(const FloatingObject& floater, const vec3& position);

	// Scales with mass.
	float CalculateMomentOfInertia(const float l, const float b) const;
	vec3 GetRelativeFloaterPos(const FloatingObject& floater) const;

private:
	std::vector<FloatingObject> m_Floaters;
	const WaveManager* m_WaveManager;

	SailObject m_SailObject;
	
	BoatObject::BoatDimensions m_BoatDimensions;
};