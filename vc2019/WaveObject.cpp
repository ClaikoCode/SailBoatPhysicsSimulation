#include "Includes/WaveObject.h"

constexpr vec3 DEFAULT_WATER_COLOR = vec3(0.0f, 84.0f, 147.0f) / 255.0f;
constexpr float WATER_SIZE = 500.0f;
constexpr uint32_t SUB_DIVISION = 10;

WaveObject::WaveObject() 
	: GameObject()
{
	DefaultInit();
}

WaveObject::WaveObject(const float waterSize)
{
	geom::Plane planeSource = geom::Plane();
	planeSource.size(vec2(waterSize));
	planeSource.subdivisions(ivec2(SUB_DIVISION));
	SetMesh(planeSource);

	m_MeshColor = DEFAULT_WATER_COLOR;
}

void WaveObject::Draw()
{
	DefaultDraw();
}

void WaveObject::DefaultInit()
{
	geom::Plane planeSource = geom::Plane();
	planeSource.size(vec2(WATER_SIZE));
	planeSource.subdivisions(ivec2(SUB_DIVISION));
	SetMesh(planeSource);

	m_MeshColor = DEFAULT_WATER_COLOR;
}
