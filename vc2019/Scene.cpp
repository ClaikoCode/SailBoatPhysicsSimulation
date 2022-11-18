#include "Includes/Scene.h"

void Scene::SetupCamera()
{
	m_Camera.lookAt(vec3(2.0f, 3.0f, 1.0f), vec3(0));
	m_Camera.setPerspective(40.0f, getWindowAspectRatio(), 0.01f, 300.0f);
	m_CameraUI = CameraUi(&m_Camera, getWindow());
}
