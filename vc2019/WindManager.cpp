#include "Includes/WindManager.h"
#include "Includes/NaturalConstants.h"
#include "Includes/MathHelpers.h"


constexpr float DEFAULT_ZOOM_LEVEL = 0.02f;
constexpr uint32_t DEFAULT_OCTAVES = 2;
constexpr float MAX_WIND_FORCE = 10.0f;
constexpr float DEFAULT_TIME_SCALING = 0.05f;

// 3D Perlin noise max value: sqrt(N) / 2, where N is the dimensions of the perlin noise.
// Source (https://digitalfreepen.com/2017/06/20/range-perlin-noise.html#:~:text=TL%3BDR%3A%20The%20range%20is,assuming%20continuous%20unit%20gradient%20vectors.)
constexpr float PERLIN_MAX_VAL = 0.86602540378f; // Value is equal to sqrt(N = 3) / 2

WindManager::WindManager()
	: WindManager(DEFAULT_ZOOM_LEVEL, DEFAULT_TIME_SCALING) {}

WindManager::WindManager(const float zoomLevel)
	: WindManager(zoomLevel, DEFAULT_TIME_SCALING) {}

WindManager::WindManager(const float zoomLevel, const float timeScaling) 
	: m_Perlin(DEFAULT_OCTAVES),
	m_ZoomLevel(zoomLevel),
	m_TimeScaling(timeScaling),
	m_TimePassed(0.0f) {}

void WindManager::StepTime(const float deltaTime)
{
	m_TimePassed += deltaTime * m_TimeScaling;
}

glm::vec3 WindManager::GetWindDirAtPos(const vec2 worldPosition) const
{
	float perlinValue = GetPerlinValueAtPos(worldPosition);
	float perlinAngle = perlinValue * NaturalConstants::TWO_PI;

	// Rotate unit X vector around the Y axis.
	return glm::rotate(MathHelpers::RIGHT_VEC, perlinAngle, MathHelpers::UP_VEC);
}

glm::vec3 WindManager::GetWindDirAtPos(const vec3 worldPosition) const
{
	const vec2 xzPlanePos = vec2(worldPosition.x, worldPosition.z);
	return GetWindDirAtPos(xzPlanePos);
}

cinder::vec3 WindManager::GetWindForceAtPos(const vec3 worldPosition) const
{
	const vec3 windDir = GetWindDirAtPos(worldPosition);

	const float timeOffset = 1000.0f;
	const float forceMagnitude = GetSingleOctaveValueAtPos(worldPosition) * MAX_WIND_FORCE;

	return windDir * forceMagnitude;
}

float WindManager::GetPerlinValueAtPos(const vec2 worldPosition) const
{
	const vec2 zoomedPosition = worldPosition * m_ZoomLevel;
	const float perlinValue = m_Perlin.fBm(vec3(zoomedPosition, m_TimePassed));

	// Sigmoid clamping interpolation of perlin value.
	return glm::smoothstep(-PERLIN_MAX_VAL, PERLIN_MAX_VAL, perlinValue); 
}

float WindManager::GetSingleOctaveValueAtPos(const vec2 worldPosition) const
{
	const vec2 zoomedPosition = worldPosition * m_ZoomLevel;
	const float perlinValue = m_Perlin.noise(vec3(zoomedPosition, m_TimePassed));

	// Sigmoid clamping interpolation of perlin value.
	return glm::smoothstep(-PERLIN_MAX_VAL, PERLIN_MAX_VAL, perlinValue);
}

void WindManager::VisualizeField(const uint32_t width, const uint32_t length, const float offset)
{
	const vec3 verticalOffset = vec3(0.0f, 10.0f, 0.0f);
	// Gets the center point of a square with side length of offset.
	const vec3 squareOffset = vec3(offset / 2.0f, 0.0f, -offset / 2.0f);

	const float halfWidth = width / 2.0f;
	const float halfLength = length / 2.0f;

	const float headLength = 2.0f;
	const float headBaseRadius = headLength / 2.0f;

	for (float x = -halfWidth; x < halfWidth; x += offset)
	{
		for (float z = -halfLength; z < halfLength; z += offset)
		{
			vec3 startPoint = vec3(x, 0.0f, z) + squareOffset + verticalOffset;
			vec3 windVec = GetWindForceAtPos(startPoint);
			vec3 endPoint = windVec + startPoint;

			gl::drawVector(startPoint, endPoint, headLength, headBaseRadius);
		}
	}
}
