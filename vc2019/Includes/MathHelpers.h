#pragma once

#include "Includes/CinderEssentials.h"


namespace MathHelpers
{
	// ---- HELPFUL OBJECT DEFINITIONS ----
	
	// X unit vector.
	constexpr vec3 RIGHT_VEC = vec3(1.0f, 0.0f, 0.0f);
	// Y unit vector.
	constexpr vec3 UP_VEC = vec3(0.0f, 1.0f, 0.0f);
	// Z unit vector.
	constexpr vec3 FORWARD_VEC = vec3(0.0f, 0.0f, 1.0f);

	// ---- HELPFUL FUNCTIONS ----

	// Gives a clamped value between 0.0 and 1.0 depending on where value sits in the interval [minVal, maxVal]. 
	float InverseLerp(const float value, const float minVal, const float maxVal);

	// Runs inverse lerp on all values in 2D vector.
	vec2 InverseLerp(const vec2 values, const float minVal, const float maxVal);

	// Runs inverse lerp on all values in 3D vector.
	vec3 InverseLerp(const vec3 values, const float minVal, const float maxVal);

	// Remaps values between input min and max to another value between output min and max.
	float Remap(const float value, const float inputMin, const float inputMax, const float outputMin, const float outputMax);

	// Runs remap on all values in 2D vector.
	vec2 Remap(const vec2 values, const float inputMin, const float inputMax, const float outputMin, const float outputMax);

	// Projects the vector 'a' onto vector 'b'.
	vec3 ProjectVector(const vec3 a, const vec3 b);
};
