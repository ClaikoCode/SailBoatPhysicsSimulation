#pragma once

#include "Includes/GameObject.h"

class WaveObject : public GameObject
{
public:
	WaveObject();
	WaveObject(const float waterSize);
	~WaveObject() = default;

	void Draw() override;
	void Update() override {};

	float GetWaterSize() const;

private:
	void InitWaterPlane(const float waterSize, const uint32_t subdivisions);

private:
	float m_WaterSize;
};