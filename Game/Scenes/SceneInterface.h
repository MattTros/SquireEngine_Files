#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../../Engine/Core/Engine.h"
#include <queue>

class SceneInterface {

public:
	SceneInterface() {}
	~SceneInterface() {}

	virtual bool Initialize() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() = 0;
};

#endif // !SCENE_MANAGER_H