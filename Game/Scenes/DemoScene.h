#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#define BASE_SHADER Shader::GetInstance()->GetShader("baseShader")
#define TRANS_SHADER Shader::GetInstance()->GetShader("alphaShader")

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
#include "../../Engine/UI/DemoUI.h"

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

private:
	float timer = 0.0f;
	float stateTime = 5.0f;
	int state = 0;
	int finalState = 13;

	void State_Title();
	void State_AudioManager();				 //Incomplete
	void State_OBJLoader();					 //Complete
	void State_InputManagers();				 //Complete
	void State_Lighting();					 //Incomplete
	void State_Shader();					 //Incomplete
	void State_Physics();					 //Complete
	void State_Collision();					 //Complete
	void State_UI();						 //Complete
	void State_Textures();					 //Complete
	void State_Options();					 //Complete
	void State_Particles();					 //Complete
	void State_ParallaxingBackground();      //Incomplete
	void State_AIEnemies();					 //Incomplete
private:
	//UI stuff
	DemoUI* UI;
	Window* window;

	//Objects
	GameObject* gameOBJ;
	LightSource* light;
	ParticleSystem* particleFountain;
	GameObject* blocks[9];
	Platform *p1;
	Platform *p2;
	Platform *p3;
	ParticleSystem* shaderFountain;
	Model* transOne;
	ParallaxingBackground* parallax;
	Fly* fly;
	Ooze* ooze;
	Ooze* ooze2;
	Spiker* spiker;
	float colourChange;
};

#endif // !DEMOSCENE_H


