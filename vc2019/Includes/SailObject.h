#pragma once

#include "Includes/GameObject.h"

class SailObject : public GameObject
{
public:
	SailObject();
	~SailObject() = default;

	void Update() override;
	void Draw() override;

	// Does not turn past 90 degrees.
	void TurnSail(const float angleDelta);

	float GetSailHeight() const;
	float GetSailWidth() const;
	
	vec3 GetSailDirection() const;

private:
	void InitSailMesh();

private:
	// Sail angle in radians around the y-axis.
	float m_SailAngle;

	float m_SailHeight;
	float m_SailWidth;
};
