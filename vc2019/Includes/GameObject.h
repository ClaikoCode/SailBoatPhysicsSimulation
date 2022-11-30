#pragma once
#include "Includes/CinderEssentials.h"
#include "Includes/Transform.h"


class GameObject
{
public:
	GameObject();
	GameObject(const Transform& transform);

	~GameObject() = default;

	virtual void Draw() = 0;
	virtual void Update() = 0;

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

public:
	Transform m_Transform;
	bool m_IsStatic;
	bool m_IsDrawable;
};