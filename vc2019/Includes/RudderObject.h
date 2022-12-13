#pragma once
#include "Includes/GameObject.h"
#include "Includes/CinderEssentials.h"

class RudderObject : public Object
{
public:
	RudderObject();
	RudderObject(const float rudderHeight, const float rudderWidth);
	~RudderObject() = default;

	virtual void Draw() override;
	virtual void Update() override {};

	void TurnRudder(const float angleDelta);
	vec3 GetRudderGlobalPosition();

private:
	void InitRudderModel();

private:
	GameObject m_RudderModel;

	float m_RudderAngle;

	float m_RudderHeight;
	float m_RudderWidth;
	float m_RudderArea;
};