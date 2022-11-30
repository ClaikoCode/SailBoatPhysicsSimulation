#pragma once
#include "Includes/CinderEssentials.h"

namespace NaturalConstants
{
	constexpr float PI = 3.141592f;
	constexpr float TWO_PI = PI * 2.0f;
	constexpr float PI_HALF = PI / 2.0f;
	constexpr float PI_FOURTH = PI / 4.0f;


	constexpr float DENSITY_WATER = 100.0f;
	constexpr float GRAVITATIONAL_CONSTANT = 20.0f;
	constexpr vec3 gravity = vec3(0.0f, -GRAVITATIONAL_CONSTANT, 0.0f);
}