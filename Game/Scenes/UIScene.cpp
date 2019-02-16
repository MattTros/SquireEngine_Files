#include "UIScene.h"

UIScene::UIScene() {

}

UIScene::~UIScene() {

}

bool UIScene::Initialize()
{
	std::string texturePath = "Resources/Textures/";

	Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.7f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f)));
	TextureHandler::GetInstance()->CreateTexture("playdrunnerTexture", texturePath + "PlaydRunnerLogoCircleCircuit.png");
	CollisionHandler::GetInstance()->Initialize(100.0f);

	UI = new MainMenu();
	window = Engine::GetInstance()->Engine::GetWindow();
	UI->Initialize(window->GetWindow(), window->GetContext());
	uiState = UI->state;

	return true;
}

void UIScene::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);
	UpdateUI(deltaTime_);
}

void UIScene::Render()
{
	if (UI != nullptr)
		UI->Render();
}

void UIScene::UpdateUI(const float deltaTime_) {
	//If the state has changed, set the state correctly, and change where the UIManager is pointing.(Jake Cunningham)
	if (UI != nullptr) {
		if (uiState != UI->state) {
			//set our local state to the actual state for comparision
			uiState = UI->state;
			switch (uiState) {
			case 0:
				//delete UI 

				printf("State 0\n");
				delete UI;
				UI = nullptr;
				break;
			case 1:
				//delete UI 
				delete UI;
				UI = nullptr;
				//init a new Main Menu
				printf("State 1\n");
				UI = new MainMenu();
				UI->Initialize(window->GetWindow(), window->GetContext());
				break;
			case 2:
				//delete UI 
				delete UI;
				UI = nullptr;
				//Init a new options menu
				printf("State 2\n");
				UI = new OptionsMenu();
				UI->Initialize(window->GetWindow(), window->GetContext());
				uiState = 2;
				UI->state = 2;
				break;
			}
		}
	}
	if (UI != nullptr)
		UI->Update(deltaTime_);
}