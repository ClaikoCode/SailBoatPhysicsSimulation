#include "Includes/WaveManager.h"
#include "cinder/Log.h"

#include "Includes/WindManager.h"
#include "Includes/PhysicsObject.h"
#include "Includes/NaturalConstants.h"
#include "Includes/MathHelpers.h"

constexpr float WAVE_AMPLITUDE = 5.0f;
constexpr float DEFAULT_TIME_STEP = 0.5f;
constexpr float DEFAULT_WAVE_LENGTH = 75.0f;

WaveManager::WaveManager()
	: m_WaveObject(), m_TimePassed(0.0f) {}

void WaveManager::CalculateWaveVerticies()
{
	static WindManager windManager = WindManager(0.01f, 0.05f);
	windManager.StepTime(0.02f);

	TriMeshRef waveTriMesh = m_WaveObject.GetTriMesh();
	size_t numVertecies = waveTriMesh->getNumVertices();
	vec3* vertexPositions = waveTriMesh->getPositions<3>();
	Colorf* vertexColors = waveTriMesh->getColors<3>();
	
	vec3 seaOffset = vec3(250.0f, 0.0f, 250.0f);

	for (int i = 0; i < numVertecies; i++)
	{
		vec3& vertexPos = vertexPositions[i];
		vertexPos.y = CalculateWaveHeight(vertexPos.x, vertexPos.z);
		
		vec3 worldPos = vertexPos + seaOffset * 1.0f;
		//vec2 posVec = MathHelperFunctions::InverseLerp(vec2(worldPos.x, worldPos.z), 0.0f, 500.0f);
		vec2 posVec = vec2(worldPos.x, worldPos.z);
		float perlinValue = windManager.GetPerlinValueAtPos(posVec);
		vertexColors[i] = Color(CM_RGB, vec3(perlinValue));

		//CI_LOG_D("Pos: " << vertexPos << " Value: " << perlinValue);
	}

	waveTriMesh->recalculateNormals();
	m_WaveObject.UpdateBatchMesh();
}

void WaveManager::StepTime()
{
	m_TimePassed += DEFAULT_TIME_STEP;
}

void WaveManager::DrawWaves()
{
	m_WaveObject.Draw();
}

float WaveManager::CalculateWaveHeight(const float x, const float z) const
{
	float height = glm::sin((x + m_TimePassed) / DEFAULT_WAVE_LENGTH) + glm::sin((z + m_TimePassed * 2.0f) / DEFAULT_WAVE_LENGTH);

	return height * WAVE_AMPLITUDE;
}
