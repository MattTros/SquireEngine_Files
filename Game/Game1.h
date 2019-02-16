#ifndef GAME1_H
#define GAME1_H

#define BASE_SHADER Shader::GetInstance()->GetShader("baseShader")

#include "../Engine/Core/Engine.h"
#include <glm/gtx/string_cast.hpp>
#include "ParallaxingBackground.h"
#include "GameObjects/Platform.h"
#include "GameObjects/MovingPlatform.h"
#include "Scenes/SceneManager.h"
#include "Scenes/UIScene.h"
#include "Scenes/Scene1.h"

class Game1 : public GameInterface
{
public:
	Game1();
	virtual ~Game1();

	virtual bool Initialize();
	virtual void Update(const float deltaTime_);
	virtual void Render();

	void SetScene(SceneManager* newScene_);

private:
	//Scene stuff
	SceneManager* scene;

};

#endif // !GAME1_H
