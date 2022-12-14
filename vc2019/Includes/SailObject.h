#pragma once

#include "Includes/GameObject.h"

class SailObject : public GameObject
{
public:
	SailObject();
	~SailObject() = default;

	void Update() override {};
	void Draw() override;

	// Expects angle in radians. 
	void TurnSail(const float angleDelta);

	float GetSailHeight() const;
	float GetSailWidth() const;
	
	vec3 GetGlobalSailDirection() const;
	vec3 GetLocalSailDirection() const;

private:
	void InitSailMesh();

private:
	// Sail angle in radians around the y-axis. Should only exist in range [-90, 90] degrees.
	float m_SailAngle;

	float m_SailHeight;
	float m_SailWidth;
};
