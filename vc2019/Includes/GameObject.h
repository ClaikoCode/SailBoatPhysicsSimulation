#pragma once
#include "Includes/CinderEssentials.h"
#include "Includes/Transform.h"
#include "Includes/Object.h"


class GameObject : public Object
{
public:
	GameObject();
	GameObject(const Transform& transform);

	~GameObject() = default;

	virtual void Draw() override;
	virtual void Update() override {};

	void SetMesh(const geom::Source& geometrySource);
	void SetMeshColor(const vec3 rgbColor);
	TriMeshRef GetTriMesh() const;
	void UpdateBatchMesh();

protected:
	void DefaultDraw();
	
protected:
	gl::GlslProgRef m_ShaderRef;
	gl::BatchRef m_Mesh;
	TriMeshRef m_TriMesh;

	// RGB Mesh color.
	vec3 m_MeshColor;
};