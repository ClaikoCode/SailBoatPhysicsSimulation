#include "Includes/MathHelperFunctions.h"


float MathHelperFunctions::InverseLerp(const float value, const float minVal, const float maxVal)
{
	return glm::clamp((value - minVal) / (maxVal - minVal), 0.0f, 1.0f);
}

glm::vec2 MathHelperFunctions::InverseLerp(const vec2 values, const float minVal, const float maxVal)
{
	const float newX = InverseLerp(values.x, minVal, maxVal);
	const float newY = InverseLerp(values.y, minVal, maxVal);

	return vec2(newX, newY);
}

glm::vec3 MathHelperFunctions::InverseLerp(const vec3 values, const float minVal, const float maxVal)
{
	const float newX = InverseLerp(values.x, minVal, maxVal);
	const float newY = InverseLerp(values.y, minVal, maxVal);
	const float newZ = InverseLerp(values.z, minVal, maxVal);

	return vec3(newX, newY, newZ);
}

float MathHelperFunctions::Remap(const float value, const float inputMin, const float inputMax, const float outputMin, const float outputMax)
{
	const float t = InverseLerp(value, inputMin, inputMax);
	return glm::lerp(outputMin, outputMax, t);
}

glm::vec2 MathHelperFunctions::Remap(const vec2 values, const float inputMin, const float inputMax, const float outputMin, const float outputMax)
{
	const float newX = Remap(values.x, inputMin, inputMax, outputMin, outputMax);
	const float newY = Remap(values.y, inputMin, inputMax, outputMin, outputMax);

	return vec2(newX, newY);
}
