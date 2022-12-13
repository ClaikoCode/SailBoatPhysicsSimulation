#include "Includes/Transform.h"

Transform::Transform()
	: Transform(vec3(0.0f), vec3(0.0f), vec3(1.0f)) {}

Transform::Transform(const vec3 pos, const vec3 rot, const vec3 scale) 
	: m_Position(pos), m_Scale(scale), m_Rotation(rot), m_Parent(nullptr) {}

cinder::mat4 Transform::GetGlobalTransform() const
{
	mat4 globalTransform = GetLocalTransform();
		
	if (m_Parent != nullptr)
	{
		globalTransform = m_Parent->GetGlobalTransform() * globalTransform; // Order is important!
	}

	return globalTransform;
}

cinder::mat4 Transform::GetLocalTransform() const
{
	mat4 localTransform =
		glm::translate(GetLocalPosition()) *
		GetLocalRotationMatrix() *
		glm::scale(GetLocalScale());

	return localTransform;
}

glm::mat4 Transform::GetLocalRotationMatrix() const
{
	return glm::eulerAngleXYZ(m_Rotation.x, m_Rotation.y, m_Rotation.z);
}

void Transform::SetParentTransform(const Transform& parent)
{
	m_Parent = &parent;
}

cinder::mat4 Transform::GetUnscaledGlobalTransform() const
{
	mat4 transformationMatrix =
		glm::translate(GetLocalPosition()) *
		GetLocalRotationMatrix();

	if (m_Parent != nullptr)
	{
		transformationMatrix = m_Parent->GetUnscaledGlobalTransform() * transformationMatrix; // Order is important!
	}

	return transformationMatrix;
}

// ----- Local transform functions -----

cinder::vec3 Transform::GetLocalPosition() const { return m_Position; }
void Transform::SetLocalPosition(const vec3& newPos) { m_Position = newPos; }
void Transform::SetLocalPosition(const float x, const float y, const float z) { m_Position = vec3(x, y, z); }
void Transform::UpdateLocalPosition(const vec3 posDelta) { m_Position += posDelta; }

cinder::vec3 Transform::GetLocalScale() const { return m_Scale; }
void Transform::SetScale(const vec3 newScale) { m_Scale = newScale; }
void Transform::SetScale(const float scaleFactor) { m_Scale = vec3(scaleFactor); }
void Transform::UpdateLocalScale(const vec3 scaleDelta) { m_Scale += scaleDelta; }
void Transform::UpdateLocalScale(const float multiplier) { m_Scale *= multiplier; }

cinder::vec3 Transform::GetLocalRotation() const { return m_Rotation; }
void Transform::SetLocalRotation(const vec3 newRot) { m_Rotation = newRot; }
void Transform::UpdateLocalRotation(const vec3 rotDelta) { m_Rotation += rotDelta; }

// ----- Global transform functions -----

cinder::vec3 Transform::GetGlobalPosition() const
{
	if (m_Parent == nullptr)
		return GetLocalPosition();

	return GetUnscaledGlobalTransform()[3]; // Gets translational part of affine matrix.
}

cinder::vec3 Transform::GetGlobalScale() const
{
	if (m_Parent == nullptr)
		return GetLocalScale();

	return m_Parent->GetGlobalScale() * GetLocalScale();
}

cinder::vec3 Transform::GetGlobalRotation() const
{
	if (m_Parent == nullptr)
		return GetLocalRotation();

	return m_Parent->GetGlobalRotation() + GetLocalRotation();
}