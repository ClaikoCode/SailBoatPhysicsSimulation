#pragma once

#include "Includes/WaveObject.h"

class WaveManager
{
public:
	WaveManager();
	
	void CalculateWaveVerticies();
	float CalculateWaveHeight(const float x, const float z) const;
	// Expects a world position.
	float CalculateWaveHeight(const vec3 worldPosition) const;

	void StepTime(const float deltaTime);
	void DrawWaves();

public:
	WaveObject m_WaveObject;
	float m_TimePassed;
};