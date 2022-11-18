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
	return glm::scale(m_Scale) * glm::translate(m_Position) * glm::eulerAngleXYZ(m_Rotation.x, m_Rotation.y, m_Rotation.z);
}


// ---- POSITION FUNCTIONS -----

glm::vec3 Transform::GetPosition() { return m_Position; }
void Transform::SetPosition(const vec3 newPos) { m_Position = newPos;}
void Transform::UpdatePosition(const vec3 posDelta) { m_Position += posDelta;}


// ---- SCALE FUNCTIONS -----

glm::vec3 Transform::GetScale() { return m_Scale; }
void Transform::SetScale(const vec3 newScale) { m_Scale = newScale;}
void Transform::UpdateScale(const vec3 scaleDelta) { m_Scale += scaleDelta;}


// ---- ROTATION FUNCTIONS -----

glm::vec3 Transform::GetRotation() { return m_Rotation; }
void Transform::SetRotation(const vec3 newRot) { m_Rotation = newRot;}
void Transform::UpdateRotation(const vec3 rotDelta) { m_Rotation += rotDelta;}
