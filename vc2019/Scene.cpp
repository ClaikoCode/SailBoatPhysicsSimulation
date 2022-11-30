#include "Includes/Scene.h"

#include "cinder/Rand.h"
#include "cinder/Timer.h"
#include "cinder/Log.h"

#include "Includes/ValueRandomizationVolume.h"
#include "Includes/FloatingObject.h"
#include "Includes/BoatObject.h"
#include "Includes/WaveObject.h"


#include "Includes/NaturalConstants.h"

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
	SetupWater();
}


void Scene::UpdateScene()
{
	float timeDelta = (float)m_WorldTimer.getSeconds();
	m_WorldTimer.start();

	//CI_LOG_D("Frame: " << getElapsedFrames());
	CI_LOG_D("Time elapsed: " << timeDelta);

	m_WaveManager.StepTime();
	m_WaveManager.CalculateWaveVerticies();
	
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
	float farPlane = 3000.0f;
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
	const float boxVal = 0.0f;
	Randomization::ValueRandomizationVolume VRV = Randomization::ValueRandomizationVolume(vec3(boxVal), vec3(0.0f, boxVal + 15.0f, 0.0f));

	WaveObject waveObject = WaveObject();
	m_GameObjects.push_back(std::make_shared<WaveObject>(waveObject));

	m_WaveManager = WaveManager();
	m_WaveManager.m_WaveObject = dynamic_cast<WaveObject*>(m_GameObjects.back().get());
	
	// Setup test objects
	BoatObject boatObject = BoatObject();
	boatObject.AttachWaveManager(m_WaveManager);
	m_PhysicsObjects.push_back(std::make_shared<BoatObject>(boatObject));
	m_GameObjects.push_back(m_PhysicsObjects.back());
}

void Scene::SetupWater()
{
	// TODO: Uncomment wavemanager.
	// m_WaveManager = WaveManager();
}


void Scene::UpdateObjects(const float deltaTime)
{
	// Update all forces for physics objects.
	for (std::shared_ptr<PhysicsObject>& physicsObject : m_PhysicsObjects)
	{
		
	}

	// Update movement for all physics objects. Should always be done after all forces in the world are properly calculated.
	for (std::shared_ptr<PhysicsObject>& physicsObject : m_PhysicsObjects)
	{
		physicsObject->PhysicsUpdate(deltaTime);
	}

	// Update other behaviours for objects.
	for (std::shared_ptr<GameObject>& gameObject : m_GameObjects)
	{
		CI_LOG_D("Local pos: " << gameObject->m_Transform.GetLocalPosition() <<
			" | Global pos: " << gameObject->m_Transform.GetGlobalPosition() <<
			" | Has transform parent: " << (gameObject->m_Transform.m_Parent != nullptr));

		gameObject->Update();
	}
}
