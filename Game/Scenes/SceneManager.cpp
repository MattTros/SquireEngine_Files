#include "SceneManager.h"

std::unique_ptr<SceneManager> SceneManager::sceneManagerInstance = nullptr;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	if (sceneMap.size() > 0)
	{
		sceneMap.clear();
	}
}

SceneManager* SceneManager::GetInstance()
{
	if (sceneManagerInstance.get() == nullptr)
	{
		sceneManagerInstance.reset(new SceneManager);
	}
	return sceneManagerInstance.get();
}

bool SceneManager::Initialize()
{
	sceneMap[sceneIndex]->Initialize();
	return true;
}

void SceneManager::Update(const float deltaTime_)
{
	if(!paused)
		sceneMap[sceneIndex]->Update(deltaTime_);
}

void SceneManager::Render()
{
	sceneMap[sceneIndex]->Render();
}

void SceneManager::AddScene(SceneInterface* scene_, int index_)
{
	if (sceneMap[index_] == nullptr)
	{
		sceneMap[index_] = scene_;
		if (sceneMap[index_] == NULL)
		{
			Debug::Error("Scene @ Index: " + std::to_string(index_) + " failed to load", __FILE__, __LINE__);
		}
	}
}

void SceneManager::SetScene(int sceneIndex_)
{
	sceneIndex = sceneIndex_;
	sceneMap[sceneIndex]->Initialize();
}

void SceneManager::Pause()
{
	paused = true;
}

void SceneManager::Unpause()
{
	paused = false;
}