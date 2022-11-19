#pragma once

#include <vector>
#include <memory>

#include "Includes/CinderEssentials.h"

#include "cinder/CameraUi.h"
#include "cinder/TriMesh.h"
#include "cinder/Rand.h"
#include "cinder/Timer.h"
#include "cinder/Log.h"

#include "Includes/PhysicsObject.h"


class Scene
{
public:

	Scene();
	~Scene();

	void SetupScene();
	void UpdateScene();
	void DrawScene();


private:
	void SetupCamera();
	void SetupObjects();

	void UpdateObjects(const float deltaTime);

	void DrawCamera();
	void DrawObjects();


private:
	Timer m_WorldTimer;

	CameraPersp m_Camera;
	CameraUi m_CameraUI;

	std::vector<std::shared_ptr<PhysicsObject>> m_PhysicsObjects;
	std::vector<std::shared_ptr<GameObject>> m_GameObjects;
};