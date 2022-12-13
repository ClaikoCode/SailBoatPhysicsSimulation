#pragma once
#include "Includes/GameObject.h"

class RudderObject : public GameObject
{
public:
	RudderObject(const float rudderHeight, const float rudderWidth);
	~RudderObject() = default;

	void TurnRudder(const float turnDelta);

private:
	Transform m_AttachementPoint;

	float m_RudderAngle;

	float m_RudderHeight;
	float m_RudderWidth;
	float m_RudderArea;
};