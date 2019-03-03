#ifndef SCENE1_H
#define SCENE1_H

#define BASE_SHADER Shader::GetInstance()->GetShader("baseShader")

#include "SceneManager.h"
#include <glm/gtx/string_cast.hpp>
#include "../ParallaxingBackground.h"
#include "../GameObjects/Platform.h"
#include "../GameObjects/MovingPlatform.h"
#include "../GameObjects/Entity.h"
#include "../Enemies/Ooze.h"
#include "../GameObjects/Wall.h"
#include "../GameObjects/Player.h"

class Scene1 : public SceneManager {
public:
	Scene1();
	~Scene1();

	bool Initialize();
	void Update(const float deltaTime_);
	void Render();

	//UI state machine and update
	void UpdateUI(const float deltaTime_);
private:
	ParticleSystem* particleFountain;

	//! Background stuff:
	ParallaxingBackground* pB;

	//Platform stuff
	Platform* platforms[5];

	//Player stuff
	Player* player;

	//Enemy Stuff
	Ooze* ooze;
};

#endif // !SCENE1_H
