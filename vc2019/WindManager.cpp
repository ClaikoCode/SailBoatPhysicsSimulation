#include "Includes/WindManager.h"
#include "Includes/NaturalConstants.h"


glm::vec2 WindManager::GetWindVecAtPos(const vec2 worldPosition, const float timePassed) const
{
	float perlinValue = GetNoiseValueAtPos(worldPosition, timePassed);
	float perlinAngle = perlinValue * NaturalConstants::TWO_PI;

	return glm::rotate(vec2(1.0f, 0.0f), perlinAngle);
}

float WindManager::GetNoiseValueAtPos(const vec2 worldPosition, const float timePassed) const
{
	return (m_Perlin.noise(vec3(worldPosition, timePassed)) + 1.0f) / 2.0f; // Scaled to give correct range of values (0.0f - 1.0f).
}
