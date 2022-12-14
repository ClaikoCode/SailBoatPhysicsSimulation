#include "Includes/SpadeRudderObject.h"
#include "Includes/NaturalConstants.h"
#include "Includes/MathHelpers.h"


constexpr float DEFAULT_RUDDER_HEIGHT = 10.0f;
constexpr float DEFAULT_RUDDER_WIDTH = 5.0f;
constexpr float DEFAULT_RUDDER_DEPTH = 0.2f;

constexpr float STALL_ANGLE = 0.3926f; // Gives max value for rudder lift coefficient. Taken from research paper.

SpadeRudderObject::SpadeRudderObject()
	: SpadeRudderObject(DEFAULT_RUDDER_HEIGHT, DEFAULT_RUDDER_WIDTH) {}

SpadeRudderObject::SpadeRudderObject(const float rudderHeight, const float rudderWidth)
	: m_RudderModel(),
	m_RudderAngle(0.0f), 
	m_RudderHeight(rudderHeight), 
	m_RudderWidth(rudderWidth), 
	m_RudderArea(),
	m_RudderAspectRatio()
{
	InitRudderModel();

	m_RudderArea = m_RudderWidth * m_RudderHeight;
	m_RudderAspectRatio = CalculateAirfoilAspectRatio();

	this->DisableDrawable();

	//TODO: Remove later
	TurnRudder(NaturalConstants::PI_FOURTH);
}


void SpadeRudderObject::Draw()
{
	m_RudderModel.Draw();
}

void SpadeRudderObject::TurnRudder(const float angleDelta)
{
	// Maximum turn angle is 90 degrees.
	if (glm::abs(m_RudderAngle + angleDelta) > NaturalConstants::PI_HALF)
		return;

	m_RudderAngle += angleDelta;
	m_Transform.UpdateLocalRotation(vec3(0.0f, angleDelta, 0.0f));
}

cinder::vec3 SpadeRudderObject::GetRudderGlobalPosition()
{
	return m_RudderModel.m_Transform.GetGlobalPosition();
}

cinder::vec3 SpadeRudderObject::GetGlobalRudderNormal() const
{
	vec3 globalNormal = vec4(MathHelpers::RIGHT_VEC, 0.0f) * m_RudderModel.m_Transform.GetGlobalTransform();
	return glm::normalize(globalNormal);
}

void SpadeRudderObject::InitRudderModel()
{
	const vec3 sizeVector = vec3(DEFAULT_RUDDER_DEPTH, m_RudderHeight, m_RudderWidth);
	geom::Cube rudderMesh = geom::Cube().size(sizeVector);
	m_RudderModel.SetMesh(rudderMesh);

	const vec3 rudderOffset = vec3(0.0f, 0.0f, -m_RudderWidth / 2.0f); // Offset rudder so that its edge rests on the Y-axis.
	m_RudderModel.m_Transform.SetLocalPosition(rudderOffset);

	m_RudderModel.m_Transform.SetParentTransform(this->m_Transform);
}

float SpadeRudderObject::CalculateAirfoilAspectRatio()
{
	// Airfoil aspect ratio is wingspan divided by the mean chord. Mean chord is just the chord for a rectangle.
	return m_RudderHeight / m_RudderWidth;
}

float SpadeRudderObject::GetLiftCoefficient() const
{
	// Sources: 
	// http://www.cembercikutuphanesi.biz.tr/propeller/appendage/sailing/a542380.pdf Used for most values.
	// https://www.sciencedirect.com/topics/engineering/stall-angle
	
	/*

	All values are based on first source and a aspect ratio of 6.0.

	Website for regression: https://planetcalc.com/8735/
	// TODO: Regress with making C_L 0 if angle of attack is 0.

	Prior stall angle regression values:
	Angle: -0.06981 0 0.0698132 0.1396 0.20944 0.2792 0.3490 0.3926
	C_L: -0.3 0 0.1 0.6 0.9 1.2 1.4 1.5
	Linear regression (Forced that y = 1.5 is cut by last x value): y = 3.8482x - 0.0108

	Post stall angle regression values:
	Angle: 0.39269908 0.401426 0.42062435 0.453786 0.488692 0.541052 1.5708
	C_L: 1.5 1.3 1.2 1.1 1 0.88 0.0
	Hyperbolic regression (Forced that y = 1.5 is cut by first value): y= -0.603702 + 0.825913 / x
	
	*/

	const float angleOfAttack = glm::abs(m_RudderAngle);
	
	float resultingCoefficient = 0.0f;
	if (angleOfAttack < STALL_ANGLE)
	{
		resultingCoefficient = 3.8482f * angleOfAttack - 0.0108f;
	}
	else
	{
		resultingCoefficient = -0.603702f + 0.825913f / angleOfAttack;
	}

	return resultingCoefficient;
}

float SpadeRudderObject::GetRudderArea() const { return m_RudderArea; }
