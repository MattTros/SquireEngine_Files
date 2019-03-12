#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>
#include "SceneInterface.h"

class SceneManager
{
public:
	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator = (const SceneManager&) = delete;
	SceneManager& operator = (SceneManager&&) = delete;

	static SceneManager* GetInstance();

	bool Initialize();
	void Update(const float deltaTime_);
	void Render();

	void SetScene(SceneInterface* newScene_);

	void Pause();
	void Unpause();
private:
	SceneManager();
	~SceneManager();

	static std::unique_ptr<SceneManager> sceneManagerInstance;
	friend std::default_delete<SceneManager>;

	SceneInterface* currentScene;
	bool paused = false;
};

#endif // !SCENEMANAGER_H



