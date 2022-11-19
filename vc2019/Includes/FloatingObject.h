#pragma once

#include "Includes/PhysicsObject.h"

class FloatingObject : public PhysicsObject
{
public:
	FloatingObject();

	~FloatingObject() = default;

	virtual void Draw() override;
	virtual void PhysicsUpdate(const float deltaTime) override;
	virtual void Update() override;

private:
	void SetMesh(const geom::Source& geometrySource);

};