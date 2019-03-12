#include "SceneManager.h"

std::unique_ptr<SceneManager> SceneManager::sceneManagerInstance = nullptr;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	if (currentScene != nullptr)
	{
		delete currentScene;
		currentScene = nullptr;
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
	currentScene->Initialize();
	return true;
}

void SceneManager::Update(const float deltaTime_)
{
	if(!paused)
		currentScene->Update(deltaTime_);
}

void SceneManager::Render()
{
	currentScene->Render();
}

void SceneManager::SetScene(SceneInterface* newScene_)
{
	currentScene = nullptr;
	delete currentScene;
	currentScene = newScene_;
	currentScene->Initialize();
}

void SceneManager::Pause()
{
	paused = true;
}

void SceneManager::Unpause()
{
	paused = false;
}