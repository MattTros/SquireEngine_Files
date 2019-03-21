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
			Debug::Error("Scene @ Index: " + std::to_string(index_) + " failed to add", __FILE__, __LINE__);
		}
	}
}

void SceneManager::SetScene(int sceneIndex_)
{
	if (sceneMap[sceneIndex_] == nullptr)
	{
		Debug::Error("Scene @ Index: " + std::to_string(sceneIndex_) + " failed to load", __FILE__, __LINE__);
	}
	else
	{
		sceneIndex = sceneIndex_;
		sceneMap[sceneIndex]->Initialize();
	}
}

int SceneManager::GetSceneIndex()
{
	return sceneIndex;
}

void SceneManager::SaveScene()
{
	if (SaveManager::GetInstance()->CheckExists("save1"))
	{
		Save save = Save();
		save.name = "save1";
		save.info = std::to_string(GetSceneIndex());
		SaveManager::GetInstance()->WriteTo(save);
	}
	else
	{
		Save save = Save();
		save.name = "save1";
		save.info = std::to_string(GetSceneIndex());
		SaveManager::GetInstance()->CreateSave("save1", save);
	}
}

void SceneManager::Pause()
{
	paused = true;
}

void SceneManager::Unpause()
{
	paused = false;
}