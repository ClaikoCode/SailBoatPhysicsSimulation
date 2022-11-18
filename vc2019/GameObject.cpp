#include "Includes/GameObject.h"

GameObject::GameObject()
{
	DefaultInit();
}

GameObject::GameObject(const Transform transform)
{
	DefaultInit();

	m_Transform = transform;
}

void GameObject::SetMesh(const geom::Source& geometrySource)
{
	m_TriMesh = TriMesh::create(geometrySource);
	m_Mesh = gl::Batch::create(*m_TriMesh, m_ShaderRef);
}

void GameObject::DefaultInit()
{
	m_ShaderRef = gl::getStockShader(gl::ShaderDef().lambert().color());
	m_Mesh = {};
	m_TriMesh = {};

	m_Transform = Transform();
}
