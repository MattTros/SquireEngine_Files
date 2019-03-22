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
#include "../GameObjects/Wall.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Flag.h"

class SceneManager;

class Scene2 : public SceneInterface {
public:
	Scene2();
	~Scene2();

	bool Initialize();
	void Update(const float deltaTime_);
	void Render();

	//UI state machine and update
	void UpdateUI(const float deltaTime_);
private:
	//Platform stuff
	GameObject* gameObjects[23];

	//Player stuff
	Player* player;

	//Enemy Stuff
	Ooze* ooze;
	Fly* fly;

	///Finish Flag
	Flag* end;
	WaitForSeconds initTimer;
};

#endif // !SCENE2_H
