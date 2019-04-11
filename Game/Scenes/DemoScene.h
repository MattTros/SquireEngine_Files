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
	int finalState = 14;

	void State_AudioManager();				 //Incomplete
	void State_OBJLoader();					 //Complete
	void State_Materials();					 //Complete
	void State_InputManagers();				 //Complete
	void State_Lighting();					 //Incomplete
	void State_Shader();					 //Incomplete
	void State_Physics();					 //Incomplete
	void State_Collision();					 //Incomplete
	void State_UI();						 //Incomplete
	void State_Textures();					 //Incomplete
	void State_Options();					 //Incomplete
	void State_Particles();					 //Complete
	void State_ParallaxingBackground();      //Incomplete
	void State_AIEnemies();					 //Incomplete
private:
	//Objects
	GameObject* gameOBJ;
	LightSource* light;
	ParticleSystem* particleFountain;
	GameObject* blocks[9];
	Ooze* ooze;
};

#endif // !DEMOSCENE_H


