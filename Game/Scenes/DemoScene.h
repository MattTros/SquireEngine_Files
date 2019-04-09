#ifndef DEMOSCENE_H
#define DEMOSCENE_H

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

class DemoScene : public SceneInterface
{
public:
	DemoScene();
	~DemoScene();

	bool Initialize();
	void Update(const float deltaTime_);
	void Render();

	void ChangeState();
	void UpdateState(float deltaTime_);

	void UpdateUI(const float deltaTime_);
private:
	float timer = 0.0f;
	float stateTime = 5.0f;
	int state = 0;
	int finalState = 17;

	void State_AudioManager();
	void State_OBJLoader();
	void State_Materials();
	void State_InputManagers();
	void State_Lighting();
	void State_Shader();
	void State_Physics();
	void State_Collision();
	void State_UI();
	void State_Textures();
	void State_Options();
	void State_Particles();
	void State_ParallaxingBackground();
	void State_Player();
	void State_AIEnemies();
	void State_Combat();
	void State_IFrames();
private:
	//Objects
	GameObject* testOBJ;																																				
};

#endif // !DEMOSCENE_H


