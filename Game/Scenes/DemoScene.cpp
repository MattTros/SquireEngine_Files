#include "DemoScene.h"



DemoScene::DemoScene()
{
}


DemoScene::~DemoScene()
{
}

bool DemoScene::Initialize()
{
	AudioManager::GetInstance()->PauseMusic();

	Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 0.0f, 3.15f));
	Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.7f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f)));

	light = Camera::GetInstance()->GetLightSources().at(0);

	CollisionHandler::GetInstance()->Initialize(100.0f);

	AudioManager::GetInstance()->StopAudioChannel(0);

	//Initialization Area
	///OBJ Loader
	Model* model = new Model("KnightSword.obj", "", BASE_SHADER);
	gameOBJ = new GameObject(model, glm::vec3(10.0f));
	gameOBJ->SetRotation(glm::vec3(0.0f, 1.0f, 0.0f));
	gameOBJ->SetPosition(glm::vec3(0.0f, -0.5f, -1.0f));
	///Particle Fountain
	Model* blue = new Model("RedFire.obj", "RedFire.mtl", BASE_SHADER);
	Model* blue2 = new Model("OrangeFire.obj", "OrangeFire.mtl", BASE_SHADER);
	particleFountain = new ParticleSystem();
	particleFountain->CreateSystem(blue, blue2, 30, glm::vec3(0.25), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), 0.5f, 1.0f);
	particleFountain->SetRadius(glm::vec3(0.0f));
	particleFountain->SetOrigin(glm::vec3(0.0f));
	particleFountain->SetRotationSpeed(5.0f);
	///Platforms
	Model* brick = new Model("Brick.obj", "Brick.mtl", BASE_SHADER);
	Model* brick2 = new Model("Brick.obj", "Brick.mtl", BASE_SHADER);
	blocks[0] = new Platform(brick, glm::vec3(0.0f, -2.0f, 0.0f), false);
	blocks[1] = new Platform(brick, glm::vec3(2.0f, -2.0f, 0.0f), false);
	blocks[2] = new Platform(brick, glm::vec3(-2.0f, -2.0f, 0.0f), false);
	blocks[3] = new Platform(brick, glm::vec3(-4.0f, -2.0f, 0.0f), false);
	blocks[4] = new Platform(brick, glm::vec3(4.0f, -2.0f, 0.0f), false);
	blocks[5] = new Wall(brick, glm::vec3(4.0f, -1.0f, 0.0f), false);
	blocks[6] = new Platform(brick, glm::vec3(4.0f, 0.0f, 0.0f), false);
	blocks[7] = new Platform(brick, glm::vec3(-4.0f, 0.0f, 0.0f), false);
	blocks[8] = new Wall(brick, glm::vec3(-4.0f, -1.0f, 0.0f), false);
	///Enemy
	Model* oozeModel = new Model("Ooze.obj", "Ooze.mtl", BASE_SHADER);
	ooze = new Ooze(oozeModel, glm::vec3(0.0f, -1.0f, 0.0f), false, nullptr);

	//Physics and collision
	p1 = new Platform(brick2, glm::vec3(-4.0f, 0.0f, 0.0f), false);
	p2 = new Platform(brick2, glm::vec3(-9.0f, 0.0f, 0.0f), false);
	p3 = new Platform(brick2, glm::vec3(-9.0f, 0.0f, 0.0f), false);

	//End of Initialization Area

	//UI stuff
	UI = new DemoUI();
	window = Engine::GetInstance()->Engine::GetWindow();
	UI->Initialize(window->GetWindow(), window->GetContext());
	ChangeState();

	return true;
}

void DemoScene::Update(float deltaTime_)
{
	timer += deltaTime_;
	if (timer >= stateTime)
	{
		if (state < finalState)
			state++;
		else
			state = 0;
		UI->demoState = state;
		ChangeState();
		timer = 0.0f;
	}
	UpdateState(deltaTime_);
	UI->Update(deltaTime_);
}

void DemoScene::Render()
{
	switch (state)
	{
	case 0:
		//Audio Manager
		///Nothing to Render
		break;
	case 1:
		//OBJ loader
		gameOBJ->GetModel()->Render(Camera::GetInstance());
		break;
	case 2:
		//Materials
		gameOBJ->GetModel()->Render(Camera::GetInstance());
		break;
	case 3:
		//Input managers
		gameOBJ->GetModel()->Render(Camera::GetInstance());
		break;
	case 4:
		//Lighting
		gameOBJ->GetModel()->Render(Camera::GetInstance());
		break;
	case 5:
		//Shader
		break;
	case 6:
		//Physics //Jake G. Cunningham
		p1->GetModel()->Render(Camera::GetInstance());
		break;
	case 7:
		//Collision //Jake G. Cunningham
		p3->GetModel()->Render(Camera::GetInstance());
		p2->GetModel()->Render(Camera::GetInstance());
		p3->OnCollision(p2);
		break;
	case 8:
		//UI
		//Done in DemoUI.cpp
		break;
	case 9:
		//Textures
		//Done in DemoUI.cpp
		break;
	case 10:
		//Options
		//Done in DemoUI.cpp
		break;
	case 11:
		//Particles
		particleFountain->Render(Camera::GetInstance());
		break;
	case 12:
		//Parallaxing Background
		break;
	case 13:
		//AI & Enemies // Jake G. Cunningham
		break;
	}
	UI->Render();
}

void DemoScene::ChangeState()
{
	switch (state)
	{
	case 0:
		//Audio Manager
		State_AudioManager();
		break;
	case 1:
		//OBJ loader
		State_OBJLoader();
		break;
	case 2:
		//Materials
		State_Materials();
		break;
	case 3:
		//Input managers
		State_InputManagers();
		break;
	case 4:
		//Lighting
		State_Lighting();
		break;
	case 5:
		//Shader
		State_Shader();
		break;
	case 6:
		//Physics
		State_Physics();
		break;
	case 7:
		//Collision
		State_Collision();
		break;
	case 8:
		//UI
		State_UI();
		break;
	case 9:
		//Textures
		State_Textures();
		break;
	case 10:
		//Options
		State_Options();
		break;
	case 11:
		//Particles
		State_Particles();
		break;
	case 12:
		//Parallaxing Background
		State_ParallaxingBackground();
		break;
	case 13:
		//AI & Enemies
		State_AIEnemies();
		break;
	}
}

void DemoScene::UpdateState(float deltaTime_)
{
	switch (state)
	{
	case 0:
		//Audio Manager
		///Nothing to Update
		break;
	case 1:
		//OBJ loader
		gameOBJ->Update(deltaTime_);
		break;
	case 2:
		//Materials
		gameOBJ->Update(deltaTime_);
		break;
	case 3:
		//Input managers
		gameOBJ->Update(deltaTime_);
		if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_A))
			gameOBJ->SetPosition(glm::vec3(gameOBJ->GetPosition().x - deltaTime_ * 3.0f, gameOBJ->GetPosition().y, gameOBJ->GetPosition().z));
		if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_D))
			gameOBJ->SetPosition(glm::vec3(gameOBJ->GetPosition().x + deltaTime_ * 3.0f, gameOBJ->GetPosition().y, gameOBJ->GetPosition().z));
		if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_W))
			gameOBJ->SetPosition(glm::vec3(gameOBJ->GetPosition().x, gameOBJ->GetPosition().y + deltaTime_ * 3.0f, gameOBJ->GetPosition().z));
		if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_S))
			gameOBJ->SetPosition(glm::vec3(gameOBJ->GetPosition().x, gameOBJ->GetPosition().y - deltaTime_ * 3.0f, gameOBJ->GetPosition().z));
		if (MouseInputManager::GetInstance()->MouseButtonDown(MouseInputManager::left))
			gameOBJ->SetAngle(gameOBJ->GetAngle() - deltaTime_ * 3.0f);
		if (MouseInputManager::GetInstance()->MouseButtonDown(MouseInputManager::right))
			gameOBJ->SetAngle(gameOBJ->GetAngle() + deltaTime_ * 3.0f);
		break;
	case 4:
		//Lighting
		gameOBJ->Update(deltaTime_);
		break;
	case 5:
		//Shader
		break;
	case 6:
		//Physics
		p1->Update(deltaTime_);
		break;
	case 7:
		//Collision
		p3->Update(deltaTime_);
		p2->Update(deltaTime_);
		break;
	case 8:
		//UI
		//Done in DumoUI.cpp
		break;
	case 9:
		//Textures
		//Done in DumoUI.cpp
		break;
	case 10:
		//Options
		//Done in DumoUI.cpp
		break;
	case 11:
		//Particles
		particleFountain->Update(deltaTime_);
		break;
	case 12:
		//Parallaxing Background
		break;
	case 13:
		//AI & Enemies
		if (ooze != nullptr) {
			ooze->Update(deltaTime_);
			for (GameObject* g : blocks) {
				ooze->CollisionResponse(g, deltaTime_);
			}
		}
		break;
	}
}

void DemoScene::State_AudioManager()
{
	AudioManager::GetInstance()->PlaySoundFX("death");
}

void DemoScene::State_OBJLoader()
{
	Model* model = new Model("KnightSword.obj", "", BASE_SHADER);
	gameOBJ = new GameObject(model);
	gameOBJ->SetRotation(glm::vec3(0.0f, 1.0f, 0.0f));
	gameOBJ->SetPosition(glm::vec3(0.0f, -0.5f, -1.0f));
}

void DemoScene::State_Materials()
{
	gameOBJ = nullptr;
	Model* model = new Model("KnightSword.obj", "KnightSword.mtl", BASE_SHADER);
	gameOBJ = new GameObject(model);
	gameOBJ->SetRotation(glm::vec3(0.0f, 1.0f, 0.0f));
	gameOBJ->SetPosition(glm::vec3(0.0f, -0.5f, -1.0f));
}

void DemoScene::State_InputManagers()
{
	///Nothing to Initialize
}

void DemoScene::State_Lighting()
{
	
}

void DemoScene::State_Shader()
{

}

void DemoScene::State_Physics()
{
	Model* brick2 = new Model("Brick.obj", "Brick.mtl", BASE_SHADER);

	p1->~Platform();
	p1 = new Platform(brick2, glm::vec3(0.0f, 1.0f, 0.0f), true);
}

void DemoScene::State_Collision()
{
	p1->GetModel()->~Model();
	Model* brick2 = new Model("Brick.obj", "Brick.mtl", BASE_SHADER);

	p1->isGravity = false;

	p2->~Platform();
	p3->~Platform();

	p2 = new Platform(brick2, glm::vec3(0.0f, -2.0f, 0.0f), false); 
	p3 = new Platform(brick2, glm::vec3(0.0f, 1.0f, 0.0f), true);
	p3->isGravity = true;
}

void DemoScene::State_UI()
{
	p3->GetModel()->~Model();
	p3->isGravity = false;
}

void DemoScene::State_Textures()
{

}

void DemoScene::State_Options()
{

}

void DemoScene::State_Particles()
{
	particleFountain->StartSystem();
}

void DemoScene::State_ParallaxingBackground()
{

}

void DemoScene::State_AIEnemies()
{

}