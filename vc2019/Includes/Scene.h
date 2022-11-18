#pragma once

#include "Includes/CinderEssentials.h"

#include "cinder/CameraUi.h"
#include "cinder/TriMesh.h"
#include "cinder/Rand.h"
#include "cinder/Timer.h"
#include "cinder/Log.h"


class Scene
{
public:

	void SetupScene();

private:
	void SetupCamera();

private:
	Timer m_WorldTimer;

	CameraPersp m_Camera;
	CameraUi m_CameraUI;
};