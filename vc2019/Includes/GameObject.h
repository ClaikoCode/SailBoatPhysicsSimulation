#pragma once

#include "Includes/CinderEssentials.h"
#include "Includes/Transform.h"


class GameObject
{
public:
	GameObject();
	GameObject(const Transform transform);

	~GameObject() = default;

	virtual void Draw() = 0;
	virtual void Update() = 0;

	void SetMesh(const geom::Source& geometrySource);

private:
	void DefaultInit();

protected:
	gl::GlslProgRef m_ShaderRef;
	gl::BatchRef m_Mesh;
	TriMeshRef m_TriMesh;

	Transform m_Transform;
};