#include "Includes/RudderObject.h"


RudderObject::RudderObject(const float rudderHeight, const float rudderWidth)
	: m_AttachementPoint(),
	m_RudderAngle(0.0f), 
	m_RudderHeight(rudderHeight), 
	m_RudderWidth(rudderWidth), 
	m_RudderArea(rudderWidth * rudderHeight) 
{

}

void RudderObject::TurnRudder(const float turnDelta)
{

}
