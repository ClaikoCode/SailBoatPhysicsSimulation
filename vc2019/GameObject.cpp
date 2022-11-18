#include "Includes/GameObject.h"

GameObject::GameObject()
{
	m_Mesh = {};
	m_TriMesh = {};

	m_Transform = Transform();
}

GameObject::GameObject(const Transform transform)
{
	m_Mesh = {};
	m_TriMesh = {};

	m_Transform = transform;
}
