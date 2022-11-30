#pragma once

#include "Includes/GameObject.h"

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
	GameObject* m_WaterObject;
	float m_TimePassed;
};