#pragma once

#include "Includes/CinderEssentials.h"


namespace MathHelperFunctions
{
	// Gives a clamped value between 0.0 and 1.0 depending on where value sits in the interval [minVal, maxVal]. 
	float InverseLerp(const float value, const float minVal, const float maxVal);

	// Runs inverse lerp on all values in vector.
	vec2 InverseLerp(const vec2 values, const float minVal, const float maxVal);

	// Runs inverse lerp on all values in vector.
	vec3 InverseLerp(const vec3 values, const float minVal, const float maxVal);

	// Remaps values between input min and max to another value between output min and max.
	float Remap(const float value, const float inputMin, const float inputMax, const float outputMin, const float outputMax);

	vec2 Remap(const vec2 values, const float inputMin, const float inputMax, const float outputMin, const float outputMax);

	// Projects the vector 'a' onto vector 'b'.
	vec3 ProjectVector(const vec3 a, const vec3 b);
};

// Namespace alias for shorthand.
namespace MathFuncs = MathHelperFunctions;