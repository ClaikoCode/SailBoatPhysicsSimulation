#include "Includes/RudderObject.h"
#include "Includes/NaturalConstants.h"


constexpr float DEFAULT_RUDDER_HEIGHT = 10.0f;
constexpr float DEFAULT_RUDDER_WIDTH = 5.0f;
constexpr float DEFAULT_RUDDER_DEPTH = 0.2f;

RudderObject::RudderObject()
	: RudderObject(DEFAULT_RUDDER_HEIGHT, DEFAULT_RUDDER_WIDTH) {}

RudderObject::RudderObject(const float rudderHeight, const float rudderWidth)
	: m_RudderModel(),
	m_RudderAngle(0.0f), 
	m_RudderHeight(rudderHeight), 
	m_RudderWidth(rudderWidth), 
	m_RudderArea(rudderWidth * rudderHeight) 
{
	InitRudderModel();
}


void RudderObject::Draw()
{
	m_RudderModel.Draw();
}

void RudderObject::TurnRudder(const float angleDelta)
{
	// Maximum turn angle is 90 degrees.
	if (glm::abs(m_RudderAngle + angleDelta) > NaturalConstants::PI_HALF)
		return;

	m_RudderAngle += angleDelta;
	m_Transform.UpdateLocalRotation(vec3(0.0f, angleDelta, 0.0f));
}

cinder::vec3 RudderObject::GetRudderGlobalPosition()
{
	return m_RudderModel.m_Transform.GetGlobalPosition();
}

void RudderObject::InitRudderModel()
{
	const vec3 sizeVector = vec3(DEFAULT_RUDDER_DEPTH, m_RudderHeight, m_RudderWidth);
	geom::Cube rudderMesh = geom::Cube().size(sizeVector);
	m_RudderModel.SetMesh(rudderMesh);

	const vec3 rudderOffset = vec3(0.0f, 0.0f, -m_RudderWidth / 2.0f); // Offset rudder so that its edge rests on the Y-axis.
	m_RudderModel.m_Transform.SetLocalPosition(rudderOffset);

	m_RudderModel.m_Transform.SetParentTransform(this->m_Transform);
}
