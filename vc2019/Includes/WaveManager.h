#pragma once

#include "Includes/WaveObject.h"

class WaveManager
{
public:
	WaveManager();
	
	void CalculateWaveVerticies();
	float CalculateWaveHeight(const float x, const float z) const;

	void StepTime();

private:
	void DefaultInit();

public:
	WaveObject* m_WaveObject;
	float m_TimePassed;
};