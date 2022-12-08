#include "Includes/WindManager.h"
#include "Includes/NaturalConstants.h"
#include "Includes/MathHelperFunctions.h"

constexpr vec3 UP_VEC = vec3(0.0f, 1.0f, 0.0f);
constexpr float DEFAULT_ZOOM_LEVEL = 0.02f;

// 3D Perlin noise max value: sqrt(N = 3) / 2
// Source (https://digitalfreepen.com/2017/06/20/range-perlin-noise.html#:~:text=TL%3BDR%3A%20The%20range%20is,assuming%20continuous%20unit%20gradient%20vectors.)
constexpr float PERLIN_MAX_VAL = 0.86602540378f; 

WindManager::WindManager()
	: WindManager(DEFAULT_ZOOM_LEVEL) {}

WindManager::WindManager(const float zoomLevel)
	: m_Perlin(), m_ZoomLevel(zoomLevel) {}


glm::vec3 WindManager::GetWindDirAtPos(const vec2 worldPosition, const float timePassed) const
{
	float perlinValue = GetNoiseValueAtPos(worldPosition, timePassed);
	float perlinAngle = perlinValue * NaturalConstants::TWO_PI;

	return glm::rotate(vec3(1.0f, 0.0f, 0.0f), perlinAngle, UP_VEC);
}

cinder::vec3 WindManager::GetWindDirAtPos(const vec3 worldPosition, const float timePassed) const
{
	const vec2 xzPlanePos = vec2(worldPosition.x, worldPosition.z);
	return GetWindDirAtPos(xzPlanePos, timePassed);
}

float WindManager::GetNoiseValueAtPos(const vec2 worldPosition, const float timePassed) const
{
	const vec2 zoomedPosition = worldPosition * m_ZoomLevel;
	const float perlinValue = m_Perlin.noise(vec3(zoomedPosition, timePassed));

	// Sigmoid clamping interpolation of perlin value.
	return glm::smoothstep(-PERLIN_MAX_VAL, PERLIN_MAX_VAL, perlinValue); 
}
