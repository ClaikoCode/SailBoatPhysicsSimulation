#include "Includes/SailObject.h"
#include "Includes/NaturalConstants.h"

constexpr vec3 DEFAULT_SAIL_COLOR = vec3(255.0f) / 255.0f;
constexpr float DEFAULT_SAIL_HEIGHT = 25.0f; // Y-axis height
constexpr float DEFAULT_SAIL_WIDTH = 25.0f; // X-axis width

SailObject::SailObject()
	: GameObject()
{
	m_SailAngle = 0.0f;
	m_MeshColor = DEFAULT_SAIL_COLOR;
	
	m_SailHeight = DEFAULT_SAIL_HEIGHT;
	m_SailWidth = DEFAULT_SAIL_WIDTH;

	geom::Cube sailMesh = geom::Cube();
	sailMesh.size( vec3(m_SailWidth, m_SailHeight, 0.2f) );
	SetMesh(sailMesh);

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
	if (glm::abs(m_SailAngle + angleDelta) > NaturalConstants::PI_HALF)
		return;

	m_SailAngle += angleDelta;
}

float SailObject::GetSailHeight() const { return m_SailHeight; }
float SailObject::GetSailWidth() const { return m_SailWidth; }
