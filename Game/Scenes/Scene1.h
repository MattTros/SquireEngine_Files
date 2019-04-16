#ifndef SCENE1_H
#define SCENE1_H

#define BASE_SHADER Shader::GetInstance()->GetShader("baseShader")

#include "SceneManager.h"
#include <glm/gtx/string_cast.hpp>
#include "../ParallaxingBackground.h"
#include "../GameObjects/Platform.h"
#include "../GameObjects/MovingPlatform.h"
#include "../GameObjects/DropThroughPlatform.h"
#include "../GameObjects/Entity.h"
#include "../Enemies/Ooze.h"
#include "../Enemies/Fly.h"
#include "../Enemies/Spiker.h"
#include "../GameObjects/Wall.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/TutorialCollider.h"
#include "../GameObjects/Flag.h"
#include "../GameObjects/Spike.h"

class SceneManager;

class Scene1 : public SceneInterface {
public:
	Scene1();
	~Scene1();

	bool Initialize();
	void Update(const float deltaTime_);
	void Render();
private:
	ParticleSystem* particleFountain;

	//! Background stuff:
	ParallaxingBackground* pB;

	//Platform stuff
	GameObject* gameObjects[44];

	//Player stuff
	Player* player;

	Flag* end;
	WaitForSeconds initTimer;

	//Tutorial
	TutorialCollider* movementTutorial;
	TutorialCollider* jumpTutorial;
	TutorialCollider* dropTutorial;
	TutorialCollider* expositionCollider;
};

#endif // !SCENE1_H