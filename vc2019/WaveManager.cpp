#include "Includes/WaveManager.h"
#include "cinder/Log.h"

// TODO: REMOVE THIS WHEN DOEN
#include "Includes/WindManager.h"

constexpr float WAVE_STRENGTH = 5.0f;
constexpr float DEFAULT_TIME_STEP = 0.5f;
constexpr float DEFAULT_WAVE_LENGTH = 75.0f;

WaveManager::WaveManager()
	: m_TimePassed(0.0f)
{
	DefaultInit();
}

void WaveManager::CalculateWaveVerticies()
{
	if (m_WaveObject == nullptr)
		return;

	static WindManager windManager = WindManager();

	TriMeshRef triMesh = m_WaveObject->GetTriMesh();
	size_t numVertecies = triMesh->getNumVertices();
	vec3* vertexPositions = triMesh->getPositions<3>();
	

	for (int i = 0; i < numVertecies; i++)
	{
		vec3& vertexPos = vertexPositions[i];
		vertexPos.y = CalculateWaveHeight(vertexPos.x, vertexPos.z);
		
		float perlinValue = windManager.GetNoiseValueAtPos(vec2(vertexPos.x, vertexPos.z), 0.0f);
		//CI_LOG_D("Pos: " << vertexPos << " Value: " << perlinValue);
	}

	triMesh->recalculateNormals();
	m_WaveObject->UpdateBatchMesh();
}

void WaveManager::DefaultInit()
{
	m_WaveObject = nullptr;
	m_TimePassed = 0.0f;
}

void WaveManager::StepTime()
{
	m_TimePassed += DEFAULT_TIME_STEP;
}

float WaveManager::CalculateWaveHeight(const float x, const float z) const
{
	float height = glm::sin((x + m_TimePassed) / DEFAULT_WAVE_LENGTH) + glm::sin((z + m_TimePassed * 2.0f) / DEFAULT_WAVE_LENGTH);

	return height * WAVE_STRENGTH;
}
