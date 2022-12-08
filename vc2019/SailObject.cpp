#include "Includes/SailObject.h"
#include "Includes/NaturalConstants.h"

constexpr vec3 DEFAULT_SAIL_COLOR = vec3(255.0f) / 255.0f;
constexpr float DEFAULT_SAIL_HEIGHT = 25.0f; // Y-axis height
constexpr float DEFAULT_SAIL_WIDTH = 25.0f; // X-axis width
constexpr float DEFAULT_SAIL_DEPTH = 0.2f; // Z-axis depth (sail thinness)

SailObject::SailObject()
	: m_SailAngle(0.0f), 
	m_SailHeight(DEFAULT_SAIL_HEIGHT),
	m_SailWidth(DEFAULT_SAIL_WIDTH)
{
	InitSailMesh();
}

void SailObject::Update()
{
	m_Transform.SetLocalRotation( vec3(0.0f, m_SailAngle, 0.0f) );
}

void SailObject::Draw()
{
	DefaultDraw();
}

void SailObject::TurnSail(const float angleDelta) 
{ 
	// Maximum turn angle is 90 degrees.
	if (glm::abs(m_SailAngle + angleDelta) > NaturalConstants::PI_HALF) // TODO: sail angle will not ever hit half a circle.
		return;

	m_SailAngle += angleDelta;
}

float SailObject::GetSailHeight() const { return m_SailHeight; }
float SailObject::GetSailWidth() const { return m_SailWidth; }

glm::vec3 SailObject::GetSailDirection() const
{
	return glm::rotate(vec3(1.0f, 0.0f, 0.0f), m_SailAngle, vec3(0.0f, 1.0f, 0.0f));
}

void SailObject::InitSailMesh()
{
	geom::Cube sailMesh = geom::Cube();
	sailMesh.size(vec3(m_SailWidth, m_SailHeight, DEFAULT_SAIL_DEPTH));
	SetMesh(sailMesh);
	SetMeshColor(DEFAULT_SAIL_COLOR);
}
