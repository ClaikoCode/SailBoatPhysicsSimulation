#pragma once
#include "Includes/GameObject.h"
#include "Includes/CinderEssentials.h"

class SpadeRudderObject : public Object
{
public:
	SpadeRudderObject();
	SpadeRudderObject(const float rudderHeight, const float rudderWidth);
	~SpadeRudderObject() = default;

	virtual void Draw() override;
	virtual void Update() override {};

	void TurnRudder(const float angleDelta);
	vec3 GetRudderGlobalPosition();

	// Get the normalized direction of the rudder's normal in world space.
	vec3 GetGlobalRudderNormal() const;
	float GetLiftCoefficient() const;
	float GetRudderArea() const;

private:
	void InitRudderModel();
	float CalculateAirfoilAspectRatio();
	

public:
	GameObject m_RudderModel; // TODO: Move this to private and find a better solution for copying object to transfer parenthood.

private:
	

	float m_RudderAngle;

	float m_RudderHeight;
	float m_RudderWidth;
	float m_RudderArea;
	float m_RudderAspectRatio;
};