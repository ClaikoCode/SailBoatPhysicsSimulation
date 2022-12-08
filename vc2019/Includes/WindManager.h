#pragma once

#include "Includes/CinderEssentials.h"

#include "cinder/Perlin.h"

class WindManager 
{
public:
	WindManager();
	WindManager(const float zoomLevel);
	~WindManager() = default;

	// Expects world position in XZ plane.
	vec3 GetWindDirAtPos(const vec2 worldPosition, const float timePassed) const;
	// Expects world position.
	vec3 GetWindDirAtPos(const vec3 worldPosition, const float timePassed) const;

	// Gives perlin value between 0.0f and 1.0f.
	float GetNoiseValueAtPos(const vec2 worldPosition, const float timePassed) const;

private:
	Perlin m_Perlin;
	const float m_ZoomLevel;
	
};