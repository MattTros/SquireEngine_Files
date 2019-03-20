#ifndef FLAG_H
#define FLAG_H

#include "../../Engine/Rendering/3D/GameObject.h"
#include "../../Game/Scenes/SceneManager.h"

class Flag
{
public:
	Flag(int sceneIndex_);
	~Flag();

	void OnCollision(GameObject* other_);

private:
	int sceneIndex;
};

#endif FLAG_H