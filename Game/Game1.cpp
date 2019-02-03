#include "Game1.h"

Game1::Game1()
{
}


Game1::~Game1()
{
	
}

bool Game1::Initialize()
{
	std::string texturePath = "Resources/Textures/";

	Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.7f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f)));
	TextureHandler::GetInstance()->CreateTexture("playdrunnerTexture", texturePath + "PlaydRunnerLogoCircleCircuit.png");

	AudioManager::GetInstance()->LoadSoundFXFile("laserFX", "Laser.wav");

	CollisionHandler::GetInstance()->Initialize(100.0f);

	Model* apple = new Model("Apple.obj", "Apple.mtl", BASE_SHADER);
	Model* dice = new Model("Dice.obj", "Dice.mtl", BASE_SHADER);

	//SceneGraph::GetInstance()->AddModel(apple);
	//
	//SceneGraph::GetInstance()->AddGameObject(new GameObject(apple), "apple1");

	particleFountain = new ParticleSystem();
	particleFountain->CreateSystem(dice, 100, glm::vec3(0.05f), glm::vec3(1.0f), glm::vec3(-0.5f, 0.0f, 0.0f), glm::vec3(-0.75f, 0.0f, 0.0f), 1.0f, 2.0f);
	particleFountain->SetOrigin(glm::vec3(0));
	particleFountain->SetGravity(0.0f);
	particleFountain->SetRotationSpeed(5.0f);
	particleFountain->StartSystem();

	UI = new MainMenu();
	window = Engine::GetInstance()->Engine::GetWindow();
	UI->Initialize(window->GetWindow(), window->GetContext());
	uiState = UI->state;

	return true;
}

void Game1::Update(const float deltaTime_)
{
	particleFountain->Update(deltaTime_);

	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_W))
	{
		particleFountain->SetOrigin(particleFountain->GetOrigin() + glm::vec3(0.0f, deltaTime_, 0.0f));
	}
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_S))
	{
		particleFountain->SetOrigin(particleFountain->GetOrigin() + glm::vec3(0.0f, -deltaTime_, 0.0f));
	}
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_A))
	{
		particleFountain->SetOrigin(particleFountain->GetOrigin() + glm::vec3(-deltaTime_, 0.0f, 0.0f));
	}
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_D))
	{
		particleFountain->SetOrigin(particleFountain->GetOrigin() + glm::vec3(deltaTime_, 0.0f, 0.0f));
	}

	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_F))
	{
		AudioManager::GetInstance()->PlaySoundFX("laserFX");
	}

	

	SceneGraph::GetInstance()->Update(deltaTime_);
	UpdateUI(deltaTime_);
}

void Game1::Render()
{
	SceneGraph::GetInstance()->Render(Camera::GetInstance());
	particleFountain->Render(Camera::GetInstance());

	if (UI != nullptr)
		UI->Render();
}

void Game1::UpdateUI(const float deltaTime_) {
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