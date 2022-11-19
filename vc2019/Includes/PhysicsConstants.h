#pragma once
#include "Includes/CinderEssentials.h"

namespace PhysicsConstants
{
	constexpr float gravitationalConstant = 1.0f;
	constexpr vec3 gravity = vec3(0.0f, -gravitationalConstant, 0.0f);
}