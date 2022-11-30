#include "Includes/GameObject.h"


#define _GET_DEFAULT_SHADER() gl::getStockShader(gl::ShaderDef().lambert().color())
constexpr vec3 DEFAULT_MODEL_COLOR = vec3(1.0f);
constexpr bool DEFAULT_STATIC_STATE = false;
constexpr bool DEFAULT_DRAWABLE_STATE = true;

GameObject::GameObject()
	: m_ShaderRef(_GET_DEFAULT_SHADER()),
	m_Mesh(), 
	m_TriMesh(),
	m_Transform(), 
	m_IsStatic(DEFAULT_STATIC_STATE),
	m_IsDrawable(DEFAULT_DRAWABLE_STATE),
	m_MeshColor(DEFAULT_MODEL_COLOR) {}

GameObject::GameObject(const Transform transform)
	: m_ShaderRef(_GET_DEFAULT_SHADER()),
	m_Mesh(),
	m_TriMesh(),
	m_Transform(transform),
	m_IsStatic(DEFAULT_STATIC_STATE),
	m_IsDrawable(DEFAULT_DRAWABLE_STATE),
	m_MeshColor(DEFAULT_MODEL_COLOR) {}

void GameObject::SetMesh(const geom::Source& geometrySource)
{
	gl::VboMesh::create(geometrySource);
	m_TriMesh = TriMesh::create(geometrySource, TriMesh::Format().positions().normals().texCoords().colors(3));
	std::vector<Color> colors = std::vector<Color>(m_TriMesh->getNumVertices(), Color(CM_RGB, DEFAULT_MODEL_COLOR));
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
	m_ShaderRef = _GET_DEFAULT_SHADER();
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
