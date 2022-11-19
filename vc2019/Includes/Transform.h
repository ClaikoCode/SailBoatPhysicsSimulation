#pragma once

#include "Includes/CinderEssentials.h"

class Transform
{
public:

	Transform();
	Transform(const Transform& other) = default;
	Transform(const vec3 pos, const vec3 rot = vec3(0.0f), const vec3 scale = vec3(1.0f));

	mat4 GetTransformMatrix();

	vec3 GetPosition();
	void SetPosition(const vec3 newPos);
	void UpdatePosition(const vec3 posDelta);

	vec3 GetScale();
	void SetScale(const vec3 newScale);
	void UpdateScale(const vec3 scaleDelta);

	vec3 GetRotation();
	void SetRotation(const vec3 newRot);
	void UpdateRotation(const vec3 rotDelta);

private:
	vec3 m_Position;
	vec3 m_Scale;

	// X Y Z Euler angles in radians.
	vec3 m_Rotation;
};