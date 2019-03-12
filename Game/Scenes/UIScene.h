#ifndef UISCENE_H
#define UISCENE_H

#define BASE_SHADER Shader::GetInstance()->GetShader("baseShader")

#include "SceneInterface.h"
#include <glm/gtx/string_cast.hpp>
#include "../../Engine/UI/MainMenu.h"
#include "../../Engine/UI/OptionsMenu.h"

class SceneManager;

class UIScene : public SceneInterface {
public:
	UIScene();
	~UIScene();

	bool Initialize();
	void Update(const float deltaTime_);
	void Render();

	//UI state machine and update
	void UpdateUI(const float deltaTime_);
private:
	//UI stuff
	UIManager* UI;
	Window* window;
	//This varible is to compare against the state variable in the UIManager class.
	//I compare states so I'm not recreating the UIManager object when I don't need to. (JakeCunningham)
	int uiState;
};

#endif // !UISCENE_H
