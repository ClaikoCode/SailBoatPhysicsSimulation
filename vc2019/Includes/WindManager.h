#pragma once

#include "Includes/CinderEssentials.h"

#include "cinder/Perlin.h"

class WindManager 
{
public:
	WindManager() = default;
	~WindManager() = default;

	// Returns a vector given a certain world position.
	vec2 GetWindVecAtPos(const vec2 worldPosition, const float timePassed) const;

	// Gives perlin value between 0.0f and 1.0f.
	float GetNoiseValueAtPos(const vec2 worldPosition, const float timePassed) const;

private:

	Perlin m_Perlin;
	
};