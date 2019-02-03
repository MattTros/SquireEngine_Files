#ifndef GAME1_H
#define GAME1_H

#define BASE_SHADER Shader::GetInstance()->GetShader("baseShader")

#include "../Engine/Core/Engine.h"
#include <glm/gtx/string_cast.hpp>
#include "../Engine/UI/MainMenu.h"
#include "../Engine/UI/OptionsMenu.h"

class Game1 : public GameInterface
{
public:
	Game1();
	virtual ~Game1();

	virtual bool Initialize();
	virtual void Update(const float deltaTime_);
	virtual void Render();

	//UI state machine and update
	void UpdateUI(const float deltaTime_);
private:
	ParticleSystem* particleFountain;

	//UI stuff
	UIManager* UI;
	Window* window;
	//This varible is to compare against the state variable in the UIManager class.
	//I compare states so I'm not recreating the UIManager object when I don't need to. (JakeCunningham)
	int uiState;
};

#endif // !GAME1_H
