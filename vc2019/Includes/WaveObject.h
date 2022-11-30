#pragma once

#include "Includes/GameObject.h"

class WaveObject : public GameObject
{
public:
	WaveObject();
	// TODO: Make this more efficient as to not duplicate water mesh creation
	WaveObject(const float waterSize);
	~WaveObject() = default;

	void Draw() override;
	void Update() override {};

private:
	void DefaultInit();



};