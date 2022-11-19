#pragma once
#include <memory.h>

#include "Includes/CinderEssentials.h"

class Transform
{
public:

	Transform();
	Transform(const Transform& other) = default;
	Transform(const vec3 pos, const vec3 rot = vec3(0.0f), const vec3 scale = vec3(1.0f));

	mat4 GetTransformMatrix();

	// ----- Local transform functions -----

	vec3 GetLocalPosition();
	void SetLocalPosition(const vec3 newPos);
	void UpdateLocalPosition(const vec3 posDelta);

	vec3 GetLocalScale();
	void SetLocalScale(const vec3 newScale);
	void UpdateLocalScale(const vec3 scaleDelta);
	void UpdateLocalScale(const float multiplier);

	vec3 GetLocalRotation();
	void SetLocalRotation(const vec3 newRot);
	void UpdateLocalRotation(const vec3 rotDelta);


	// ----- Global transform functions -----

	vec3 GetGlobalPosition();
	//void SetGlobalPosition(const vec3 newPos);
	//void UpdateGlobalPosition(const vec3 posDelta);

	vec3 GetGlobalScale();
	//void SetGlobalScale(const vec3 newScale);
	//void UpdateGlobalScale(const vec3 scaleDelta);
	//void UpdateGlobalScale(const float multiplier);

	vec3 GetGlobalRotation();
	//void SetGlobalRotation(const vec3 newRot);
	//void UpdateGlobalRotation(const vec3 rotDelta);

public:
	vec3 m_Position;
	vec3 m_Scale;

	// X Y Z Euler angles in radians.
	vec3 m_Rotation;

	Transform* m_Parent;
};