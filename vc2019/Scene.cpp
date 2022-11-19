#include "Includes/Scene.h"

#include "Includes/ValueRandomizationVolume.h"

constexpr int MAX_OBJECTS = 2;

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

	//CI_LOG_D("Frame: " << getElapsedFrames());
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
	for (std::shared_ptr<GameObject>& gameObject : m_GameObjects)
	{
		gameObject->Draw();
	}
}


void Scene::SetupCamera()
{
	vec3 eyePoint = vec3(2.0f, 3.0f, 1.0f) * 70.0f;
	vec3 target = vec3(0.0f);
	m_Camera.lookAt(eyePoint, target);

	float verticalFov = 40.0f;
	float nearPlane = 0.01f;
	float farPlane = 2000.0f;
	m_Camera.setPerspective(verticalFov, getWindowAspectRatio(), nearPlane, farPlane);

	m_CameraUI = CameraUi(&m_Camera, getWindow());
}


template <typename T>
void Scene::AddObject(T& object, std::vector<std::shared_ptr<T>>& objectVector)
{
	// Faster to move resources when making shared pointers as we avoid incrementing and then immediately decrementing ptr usage count.
	std::shared_ptr<T> objectPtr = std::make_shared<T>(std::move(object));
	objectVector.push_back(std::move(objectPtr));
	m_GameObjects.push_back(objectVector.back());
}


void Scene::SetupObjects()
{
	const float boxVal = 5.0f;
	Randomization::ValueRandomizationVolume VRV = Randomization::ValueRandomizationVolume(vec3(boxVal), vec3(0.0f, boxVal + 2.0f, 0.0f));

	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		PhysicsObject physicsObject = PhysicsObject();
		physicsObject.m_Transform.SetLocalPosition(VRV.GetValue());
		//physicsObject.m_Transform.SetLocalRotation(VRV.GetValue());
		physicsObject.m_Transform.UpdateLocalScale(3.0f);
		physicsObject.SetMesh(geom::Cube());

		physicsObject.m_Mass = (float)physicsObject.m_Transform.GetLocalPosition().length();
		//physicsObject.m_AngularVelocity = VRV.GetValue();

		if (i == 1)
		{
			m_PhysicsObjects.back()->m_AngularVelocity = vec3(2.0f, 0.0f, 0.0f);
			m_PhysicsObjects.back()->m_Velocity = vec3(3.0f, 0.0f, 0.0f);
			physicsObject.m_AngularVelocity = vec3(1.0f, 0.0f, 0.0f);
			physicsObject.m_Transform.m_Parent = &(m_PhysicsObjects.back()->m_Transform);
		}

		AddObject<PhysicsObject>(physicsObject, m_PhysicsObjects);
	}

	PhysicsObject physicsObject = PhysicsObject();
	physicsObject.SetMesh(geom::Plane());
	physicsObject.m_IsStatic = true;
	physicsObject.m_Transform.UpdateLocalScale(50.0f);
	AddObject<PhysicsObject>(physicsObject, m_PhysicsObjects);
}


void Scene::UpdateObjects(const float deltaTime)
{
	// Update physics of objects.
	for (std::shared_ptr<PhysicsObject>& physicsObject : m_PhysicsObjects)
	{
		physicsObject->AddForce(vec3(0.0f));
		physicsObject->PhysicsUpdate(deltaTime);
	}

	// Update other behaviours for objects.
	for (std::shared_ptr<GameObject>& gameObject : m_GameObjects)
	{
		gameObject->Update();
	}
}
