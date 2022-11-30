#include "Includes/GameObject.h"

constexpr vec3 _DEFAULT_MODEL_COLOR = vec3(1.0f);

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
	gl::VboMesh::create(geometrySource);
	m_TriMesh = TriMesh::create(geometrySource, TriMesh::Format().positions().normals().texCoords().colors(3));
	std::vector<Color> colors = std::vector<Color>(m_TriMesh->getNumVertices(), Color(CM_RGB, _DEFAULT_MODEL_COLOR));
	m_TriMesh->appendColors(colors.data(), colors.size());

	//m_TriMesh = TriMesh::create(geometrySource);
	UpdateBatchMesh();
}

cinder::TriMeshRef GameObject::GetTriMesh() const
{
	return m_TriMesh;
}

void GameObject::UpdateBatchMesh()
{
	//Batch::AttributeMapping
	//geom::Attrib::COLOR
	m_Mesh = gl::Batch::create(*m_TriMesh, m_ShaderRef);
}

void GameObject::DefaultInit()
{
	m_ShaderRef = gl::getStockShader(gl::ShaderDef().lambert().color());
	m_Mesh = {};
	m_TriMesh = {};

	m_Transform = Transform();

	m_IsStatic = false;
	m_IsDrawable = true;

	m_MeshColor = vec3(1.0f);
}

void GameObject::DefaultDraw()
{
	if (m_IsDrawable == false)
		return;
	
	gl::ScopedModelMatrix model;
	gl::multModelMatrix(m_Transform.GetGlobalTransform());
	//gl::ScopedColor color(Colorf(CM_RGB, m_MeshColor));
	m_Mesh->draw();
}
