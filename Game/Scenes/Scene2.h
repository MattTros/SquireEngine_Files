#ifndef SCENE2_H
#define SCENE2_H

#define BASE_SHADER Shader::GetInstance()->GetShader("baseShader")

#include "SceneManager.h"
#include <glm/gtx/string_cast.hpp>
#include "../ParallaxingBackground.h"
#include "../GameObjects/Platform.h"
#include "../GameObjects/MovingPlatform.h"
#include "../GameObjects/Entity.h"
#include "../Enemies/Ooze.h"
#include "../Enemies/Fly.h"
#include "../Enemies/Spiker.h"
#include "../GameObjects/Wall.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Flag.h"
#include "../GameObjects/TutorialCollider.h"

class SceneManager;

class Scene2 : public SceneInterface {
public:
	Scene2();
	~Scene2();

	bool Initialize();
	void Update(const float deltaTime_);
	void Render();
private:
	//Platform stuff
	GameObject* gameObjects[33];

	//Player stuff
	Player* player;

	//Enemy Stuff
	Ooze* ooze;
	Fly* fly;
	Spiker* spiker;

	ParallaxingBackground* pB;
	///Finish Flag
	Flag* end;
	WaitForSeconds initTimer;

	//Tutorial
	TutorialCollider* movementTutorial;
	TutorialCollider* jumpTutorial;
};

#endif // !SCENE2_H
