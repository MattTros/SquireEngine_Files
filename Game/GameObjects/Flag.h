#ifndef FLAG_H
#define FLAG_H

#include "../../Engine/Rendering/3D/GameObject.h"
#include "../../Game/Scenes/SceneManager.h"

class Flag : public GameObject
{
public:
	Flag(Model* model_, glm::vec3 position_, int sceneIndex_);
	~Flag();

	void OnCollision(GameObject* other_);

	void Update(float deltaTime_);
	void Render(Camera* camera_);
private:
	int sceneIndex;

	GameObject* firepit;
	ParticleSystem* fire;
	ParticleSystem* smoke;
};

#endif FLAG_H