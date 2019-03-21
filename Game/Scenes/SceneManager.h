#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>
#include "SceneInterface.h"
#include "../../Engine/Events/SaveManager.h"

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

	void AddScene(SceneInterface* scene_, int index_);
	void SetScene(int sceneIndex_);

	int GetSceneIndex();

	void SaveScene();

	void Pause();
	void Unpause();
private:
	SceneManager();
	~SceneManager();

	static std::unique_ptr<SceneManager> sceneManagerInstance;
	friend std::default_delete<SceneManager>;

	std::map<int, SceneInterface*> sceneMap;
	int sceneIndex;
	bool paused = false;
};

#endif // !SCENEMANAGER_H



