#include "UIScene.h"
#include "SceneManager.h"

UIScene::UIScene() {

}

UIScene::~UIScene() {

}

bool UIScene::Initialize()
{
	std::string texturePath = "Resources/Textures/";

	Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.7f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f)));
	CollisionHandler::GetInstance()->Initialize(100.0f);

	UI = new MainMenu();
	window = Engine::GetInstance()->Engine::GetWindow();
	UI->Initialize(window->GetWindow(), window->GetContext());
	uiState = UI->state;

	Model* brick = new Model("Brick.obj", "Brick.mtl", BASE_SHADER);
	floor = new GameObject(brick, glm::vec3(0.0f, -1.7f, 0.0f));
	floor->SetScale(glm::vec3(5.0f, 1.0f, 1.0f));

	Model* box = new Model("AttackBox.obj", "AttackBox.mtl", BASE_SHADER);
	firepit = new Flag(box, glm::vec3(2.0f, -0.75f, 0.0f), 0);

	Model* swordModel = new Model("KnightSword.obj", "KnightSword.mtl", BASE_SHADER);
	sword = new GameObject(swordModel, glm::vec3(-1.0f, 0.0f, 0.0f));
	sword->SetRotation(glm::vec3(0.0f, 0.0f, 1.0f));
	sword->SetAngle(2.5f);

	return true;
}

void UIScene::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);

	firepit->Update(deltaTime_);

	UpdateUI(deltaTime_);
}

void UIScene::Render()
{
	floor->GetModel()->Render(Camera::GetInstance());
	firepit->Render(Camera::GetInstance());
	sword->GetModel()->Render(Camera::GetInstance());
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