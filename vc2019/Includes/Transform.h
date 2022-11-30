#pragma once
#include <memory.h>

#include "Includes/CinderEssentials.h"

class Transform
{
public:

	Transform();
	Transform(const Transform& other) = default;
	Transform(const vec3 pos, const vec3 rot = vec3(0.0f), const vec3 scale = vec3(1.0f));

	mat4 GetGlobalTransform() const;
	mat4 GetLocalTransform() const;

	void SetParentTransform(const Transform& parent);

	// ----- Local transform functions -----

	vec3 GetLocalPosition() const;
	void SetLocalPosition(const vec3& newPos);
	void SetLocalPosition(const float x, const float y, const float z);
	void UpdateLocalPosition(const vec3 posDelta);

	vec3 GetLocalScale() const;
	void SetScale(const vec3 newScale);
	// Sets object scale uniformly from a scale factor.
	void SetScale(const float scaleFactor);
	void UpdateLocalScale(const vec3 scaleDelta);
	// Multiples current scale uniformly with multiplier.
	void UpdateLocalScale(const float multiplier);

	vec3 GetLocalRotation() const;
	void SetLocalRotation(const vec3 newRot);
	void UpdateLocalRotation(const vec3 rotDelta);


	// ----- Global transform functions -----

	vec3 GetGlobalPosition() const;
	//void SetGlobalPosition(const vec3 newPos);
	//void UpdateGlobalPosition(const vec3 posDelta);

	vec3 GetGlobalScale() const;
	//void SetGlobalScale(const vec3 newScale);
	//void UpdateGlobalScale(const vec3 scaleDelta);
	//void UpdateGlobalScale(const float multiplier);

	vec3 GetGlobalRotation() const;
	//void SetGlobalRotation(const vec3 newRot);
	//void UpdateGlobalRotation(const vec3 rotDelta);

private:
	// Gets the transform matrix of an object without applying scale matrix.
	mat4 GetUnscaledGlobalTransform() const;

public:
	vec3 m_Position;
	vec3 m_Scale;

	// X Y Z Euler angles in radians.
	vec3 m_Rotation;

	const Transform* m_Parent;
};