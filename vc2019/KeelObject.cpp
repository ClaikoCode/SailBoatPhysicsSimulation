#include "Includes/KeelObject.h"
#include "Includes/MathHelpers.h"

glm::vec3 KeelObject::GetGlobalKeelNormal()
{
	return vec4(MathHelpers::RIGHT_VEC, 0.0f) * m_Transform.GetGlobalTransform();
}
