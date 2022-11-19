#include "Includes/Transform.h"

Transform::Transform()
{
	m_Scale = vec3(1.0f);
	m_Position = vec3(0.0f);
	m_Rotation = vec3(0.0f);
}

Transform::Transform(const vec3 pos, const vec3 rot, const vec3 scale) 
	: m_Position(pos), m_Scale(scale), m_Rotation(rot) {}

glm::mat4 Transform::GetTransformMatrix()
{
	mat4 transformationMatrix =
		glm::translate(GetLocalPosition()) *
		glm::eulerAngleXYZ(m_Rotation.x, m_Rotation.y, m_Rotation.z) *
		glm::scale(GetLocalScale());
		

	if (m_Parent != nullptr)
	{
		transformationMatrix = m_Parent->GetTransformMatrix() * transformationMatrix; // Order is important!
	}

	return transformationMatrix;
}

// ----- Local transform functions -----

glm::vec3 Transform::GetLocalPosition() { return m_Position; }
void Transform::SetLocalPosition(const vec3 newPos) { m_Position = newPos; }
void Transform::UpdateLocalPosition(const vec3 posDelta) { m_Position += posDelta; }

glm::vec3 Transform::GetLocalScale() { return m_Scale; }
void Transform::SetLocalScale(const vec3 newScale) { m_Scale = newScale; }
void Transform::UpdateLocalScale(const vec3 scaleDelta) { m_Scale += scaleDelta; }
void Transform::UpdateLocalScale(const float multiplier) { m_Scale *= multiplier; }

glm::vec3 Transform::GetLocalRotation() { return m_Rotation; }
void Transform::SetLocalRotation(const vec3 newRot) { m_Rotation = newRot; }
void Transform::UpdateLocalRotation(const vec3 rotDelta) { m_Rotation += rotDelta; }

// ----- Global transform functions -----

cinder::vec3 Transform::GetGlobalPosition()
{
	if (m_Parent == nullptr)
		return GetLocalPosition();

	return m_Parent->GetGlobalPosition() + GetLocalPosition();
}

cinder::vec3 Transform::GetGlobalScale()
{
	if (m_Parent == nullptr)
		return GetLocalScale();

	return m_Parent->GetGlobalScale() * GetLocalScale();
}

cinder::vec3 Transform::GetGlobalRotation()
{
	if (m_Parent == nullptr)
		return GetLocalRotation();

	return m_Parent->GetGlobalRotation() + GetLocalRotation();
}