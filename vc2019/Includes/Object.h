#pragma once
#include "Includes/Transform.h"

class Object
{
public:
	Object();
	Object(const Transform& transform);

	~Object() = default;

	virtual void Draw() = 0;
	virtual void Update() = 0;

	void EnableStatic();
	void DisableStatic();

	void EnableDrawable();
	void DisableDrawable();

public:
	Transform m_Transform;

protected:
	bool m_IsStatic;
	bool m_IsDrawable;
};