#pragma once

#include "Includes/CinderEssentials.h"
#include "cinder/Rand.h"

namespace Randomization
{
	struct BoxSampleVolume
	{
		// The volume that all values will be sampled from.
		vec3 boxDimensions = vec3(1.0f);

		// Offset of the sampling volume.
		vec3 boxOffset = vec3(0.0f);
	};

	class ValueRandomizationVolume
	{
	public:
		ValueRandomizationVolume();
		ValueRandomizationVolume(const vec3 dimensions, const vec3 offset = vec3(0.0f)); 

		~ValueRandomizationVolume() = default;

		vec3 GetValue();

	private:
		void SetRandSeed();

	private:
		BoxSampleVolume m_SampleVolume;
		Rand m_RNG;
	};
}

