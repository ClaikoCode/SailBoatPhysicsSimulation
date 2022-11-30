#include "Includes/WaveObject.h"

constexpr vec3 DEFAULT_WATER_COLOR = vec3(0.0f, 84.0f, 147.0f) / 255.0f;
constexpr float DEFAULT_WATER_SIZE = 500.0f;
constexpr uint32_t DEFAULT_SUB_DIVISION = 10;

WaveObject::WaveObject() 
{
	InitWaterPlane(DEFAULT_WATER_SIZE, DEFAULT_SUB_DIVISION);
}

WaveObject::WaveObject(const float waterSize)
{
	InitWaterPlane(waterSize, DEFAULT_SUB_DIVISION);
}

void WaveObject::Draw()
{
	DefaultDraw();
}

void WaveObject::InitWaterPlane(const float waterSize, const uint32_t subdivisions)
{
	geom::Plane planeSource = geom::Plane();
	planeSource.size(vec2(waterSize));
	planeSource.subdivisions(ivec2(subdivisions));
	SetMesh(planeSource);
	SetMeshColor(DEFAULT_WATER_COLOR);
}
