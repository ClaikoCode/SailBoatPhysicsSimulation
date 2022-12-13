#pragma once

#include "Includes/CinderEssentials.h"

#include "cinder/Perlin.h"

class WindManager 
{
public:
	WindManager();
	WindManager(const float zoomLevel);
	WindManager(const float zoomLevel, const float timeScaling);

	~WindManager() = default;

	void StepTime(const float deltaTime);

	// Expects world position in XZ plane.
	vec3 GetWindDirAtPos(const vec2 worldPosition) const;

	// Expects world position.
	vec3 GetWindDirAtPos(const vec3 worldPosition) const;

	// Expects world position.
	vec3 GetWindForceAtPos(const vec3 worldPosition) const;

	// Gives perlin value between 0.0f and 1.0f.
	float GetPerlinValueAtPos(const vec2 worldPosition) const;

	float GetSingleOctaveValueAtPos(const vec2 worldPosition) const;

	// Creates a vector field given a certain square of width and length. Offset determines distance between each sample.
	void VisualizeField(const uint32_t width, const uint32_t length, const float offset);

private:
	Perlin m_Perlin;
	const float m_ZoomLevel;
	const float m_TimeScaling;
	float m_TimePassed;
	
};