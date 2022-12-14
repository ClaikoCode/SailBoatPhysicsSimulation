#pragma once
#include "Includes/GameObject.h"

class KeelObject : public GameObject
{
public:
	KeelObject() = default;
	~KeelObject() = default;

	void Draw() override {};
	void Update() override {};

	// Get the direction of the keel's normal in world space.
	vec3 GetGlobalKeelNormal();
};