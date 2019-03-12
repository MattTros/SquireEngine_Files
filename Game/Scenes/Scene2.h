#ifndef SCENE2_H
#define SCENE2_H

#define BASE_SHADER Shader::GetInstance()->GetShader("baseShader")

#include "SceneManager.h"
#include <glm/gtx/string_cast.hpp>
#include "../ParallaxingBackground.h"
#include "../GameObjects/Platform.h"
#include "../GameObjects/MovingPlatform.h"

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
	ParticleSystem* particleFountain;

	//! Background stuff:
	ParallaxingBackground* pB;

	//Platform stuff
	Platform* p;
	Platform* p2;

	GameObject* go;
};

#endif // !SCENE2_H
