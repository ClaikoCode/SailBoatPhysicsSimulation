#include "Includes/GameObject.h"


#define _GET_DEFAULT_SHADER() gl::getStockShader(gl::ShaderDef().lambert().color())
constexpr vec3 DEFAULT_MODEL_COLOR = vec3(1.0f);
constexpr bool DEFAULT_STATIC_STATE = false;
constexpr bool DEFAULT_DRAWABLE_STATE = true;

GameObject::GameObject()
	: GameObject(Transform()) {}

GameObject::GameObject(const Transform& transform)
	: m_ShaderRef(_GET_DEFAULT_SHADER()),
	m_Mesh(),
	m_TriMesh(),
	m_MeshColor(DEFAULT_MODEL_COLOR),
	m_Transform(transform),
	m_IsStatic(DEFAULT_STATIC_STATE),
	m_IsDrawable(DEFAULT_DRAWABLE_STATE) {}

void GameObject::SetMesh(const geom::Source& geometrySource)
{
	m_TriMesh = TriMesh::create(geometrySource, TriMesh::Format().positions().normals().texCoords().colors(3));
	
	if (m_TriMesh->hasColors())
	{
		SetMeshColor(m_MeshColor);
	}
	else
	{
		std::vector<Color> colors = std::vector<Color>(m_TriMesh->getNumVertices(), Color(CM_RGB, m_MeshColor));
		m_TriMesh->appendColors(colors.data(), colors.size());
	}
	
	UpdateBatchMesh();
}

void GameObject::SetMeshColor(const vec3 rgbColor)
{
	m_MeshColor = rgbColor;

	Colorf* colors = m_TriMesh->getColors<3>();
	const size_t numVerticies = m_TriMesh->getNumVertices();
	const Colorf newColor = Color(CM_RGB, rgbColor);

	for (int i = 0; i < numVerticies; i++)
	{
		colors[i] = newColor;
	}

	UpdateBatchMesh();
}

cinder::TriMeshRef GameObject::GetTriMesh() const 
{ 
	return m_TriMesh; 
}

void GameObject::UpdateBatchMesh()
{
	m_Mesh = gl::Batch::create(*m_TriMesh, m_ShaderRef);
}

void GameObject::DefaultDraw()
{
	if (m_IsDrawable == false)
		return;
	
	gl::ScopedModelMatrix model;
	gl::multModelMatrix(m_Transform.GetGlobalTransform());
	m_Mesh->draw();
}
