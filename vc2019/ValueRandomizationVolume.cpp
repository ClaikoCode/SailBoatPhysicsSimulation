#include <time.h>

#include "Includes/ValueRandomizationVolume.h"


Randomization::ValueRandomizationVolume::ValueRandomizationVolume()
{
	SetRandSeed();

	m_SampleVolume = {};
}

Randomization::ValueRandomizationVolume::ValueRandomizationVolume(const vec3 dimensions, const vec3 offset /* = vec3(0.0f) */)
{
	SetRandSeed();

	m_SampleVolume.boxDimensions = dimensions;
	m_SampleVolume.boxOffset = offset;
}

glm::vec3 Randomization::ValueRandomizationVolume::GetValue()
{
	const float xDist = m_SampleVolume.boxDimensions.x;
	const float yDist = m_SampleVolume.boxDimensions.y;
	const float zDist = m_SampleVolume.boxDimensions.z;

	vec3 returnVec = vec3(m_RNG.nextFloat(-xDist, xDist), m_RNG.nextFloat(-yDist, yDist), m_RNG.nextFloat(-zDist, zDist));
	return returnVec + m_SampleVolume.boxOffset;
}

void Randomization::ValueRandomizationVolume::SetRandSeed()
{
	m_RNG = Rand((uint32_t)time(0));
}
