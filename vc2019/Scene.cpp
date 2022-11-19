#include "Includes/Scene.h"

#include "Includes/ValueRandomizationVolume.h"

constexpr int MAX_OBJECTS = 20;

Scene::Scene()
{
	m_WorldTimer = Timer(false);

	m_Camera = {};
	m_CameraUI = {};

	m_PhysicsObjects = {};
}


Scene::~Scene()
{

}


void Scene::SetupScene()
{
	SetupCamera();
	SetupObjects();
}


void Scene::UpdateScene()
{
	float timeDelta = (float)m_WorldTimer.getSeconds();
	m_WorldTimer.start();

	CI_LOG_D("Frame: " << getElapsedFrames());
	CI_LOG_D("Time elapsed: " << timeDelta);
	//CI_LOG_D("Frame rate: " << getFrameRate());

	UpdateObjects(timeDelta);
}


void Scene::DrawScene()
{
	DrawCamera();
	DrawObjects();
}


void Scene::DrawCamera()
{
	gl::enableDepth(true);
	gl::setMatrices(m_Camera);
}


void Scene::DrawObjects()
{
	for (std::shared_ptr<PhysicsObject>& physicsObject : m_PhysicsObjects)
	{
		physicsObject->Draw();
	}
}


void Scene::SetupCamera()
{
	m_Camera.lookAt(vec3(2.0f, 3.0f, 1.0f) * 10.0f, vec3(0));
	m_Camera.setPerspective(40.0f, getWindowAspectRatio(), 0.01f, 300.0f);
	m_CameraUI = CameraUi(&m_Camera, getWindow());
}


void Scene::SetupObjects()
{
	const float boxVal = 10.0f;
	static Randomization::ValueRandomizationVolume VRV = Randomization::ValueRandomizationVolume(vec3(boxVal));

	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		Transform transform = Transform();
		transform.SetPosition(VRV.GetValue());
		transform.SetRotation(VRV.GetValue());
		PhysicsObject physicsObject = PhysicsObject(transform);
		physicsObject.SetMesh(geom::Cube());
		physicsObject.m_Mass = (float)transform.GetPosition().length();
		physicsObject.m_AngularVelocity = vec3(2.0f, 0.0f, 0.0f);

		m_PhysicsObjects.push_back(std::make_shared<PhysicsObject>(physicsObject));
		m_GameObjects.push_back(m_PhysicsObjects.back());
	}
}


void Scene::UpdateObjects(const float deltaTime)
{
	for (std::shared_ptr<PhysicsObject>& physicsObject : m_PhysicsObjects)
	{
		physicsObject->ApplyForce(vec3(3.0f), deltaTime);
		physicsObject->PhysicsUpdate(deltaTime);
		physicsObject->Update();
	}
}
