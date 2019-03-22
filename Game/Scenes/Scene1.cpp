#include "Scene1.h"
#include "SceneManager.h"

Scene1::Scene1() {

}
Scene1::~Scene1() {

}

bool Scene1::Initialize()
{

	Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.7f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f)));
	

	AudioManager::GetInstance()->LoadSoundFXFile("laserFX", "Laser.wav");

	CollisionHandler::GetInstance()->Initialize(100.0f);

	//! Create background images:
	//pB = new ParallaxingBackground();
	//pB->Initialize();

	///Level Layout Start
	Model* platform = new Model("Platform.obj", "Platform.mtl", BASE_SHADER);
	Model* brick = new Model("Brick.obj", "Brick.mtl", BASE_SHADER);

	gameObjects[0] = new Platform(brick, glm::vec3(0.0f, -2.0f, 0.0f), false);
	gameObjects[1] = new Platform(brick, glm::vec3(2.0f, -2.0f, 0.0f), false);
	gameObjects[2] = new Platform(brick, glm::vec3(-2.0f, -2.0f, 0.0f), false);
	gameObjects[3] = new Platform(brick, glm::vec3(4.0f, -2.0f, 0.0f), false);
	gameObjects[4] = new Platform(brick, glm::vec3(6.0f, -2.0f, 0.0f), false);
	gameObjects[5] = new Platform(platform, glm::vec3(10.0f, -2.0f, 0.0f), false); ///First jump puzzle
	gameObjects[6] = new Platform(brick, glm::vec3(7.0f, -3.0f, 0.0f), false);
	gameObjects[7] = new Platform(brick, glm::vec3(8.0f, -4.0f, 0.0f), false);
	gameObjects[8] = new Platform(brick, glm::vec3(10.0f, -4.0f, 0.0f), false);
	gameObjects[9] = new Platform(brick, glm::vec3(12.0f, -4.0f, 0.0f), false);
	gameObjects[10] = new Platform(brick, glm::vec3(14.0f, -4.0f, 0.0f), false);
	gameObjects[11] = new Platform(brick, glm::vec3(14.0f, -3.0f, 0.0f), false);
	gameObjects[12] = new Platform(brick, glm::vec3(14.0f, -2.0f, 0.0f), false);
	gameObjects[13] = new Platform(brick, glm::vec3(16.0f, -2.0f, 0.0f), false);
	gameObjects[14] = new Platform(brick, glm::vec3(18.0f, -2.0f, 0.0f), false);
	gameObjects[15] = new Platform(platform, glm::vec3(20.0f, -2.0f, 0.0f), false); ///Drop through platform
	gameObjects[16] = new Platform(brick, glm::vec3(22.0f, -2.0f, 0.0f), false);
	gameObjects[17] = new Platform(brick, glm::vec3(22.0f, -1.0f, 0.0f), false);
	gameObjects[18] = new Platform(brick, glm::vec3(22.0f, 0.0f, 0.0f), false);
	gameObjects[19] = new Platform(brick, glm::vec3(22.0f, -3.0f, 0.0f), false);
	gameObjects[20] = new Platform(brick, glm::vec3(22.0f, -4.0f, 0.0f), false);
	gameObjects[21] = new Platform(brick, glm::vec3(22.0f, -5.0f, 0.0f), false);
	gameObjects[22] = new Platform(brick, glm::vec3(22.0f, -6.0f, 0.0f), false);
	gameObjects[23] = new Platform(brick, glm::vec3(20.0f, -6.0f, 0.0f), false);
	gameObjects[24] = new Platform(brick, glm::vec3(19.0f, -7.0f, 0.0f), false);
	gameObjects[25] = new Platform(brick, glm::vec3(18.0f, -8.0f, 0.0f), false);
	gameObjects[26] = new Platform(brick, glm::vec3(17.0f, -9.0f, 0.0f), false);
	gameObjects[27] = new Platform(brick, glm::vec3(15.0f, -9.0f, 0.0f), false);
	gameObjects[28] = new Platform(brick, glm::vec3(15.0f, -10.0f, 0.0f), false);
	gameObjects[29] = new Platform(brick, glm::vec3(15.0f, -11.0f, 0.0f), false);
	gameObjects[30] = new Platform(brick, glm::vec3(13.0f, -11.0f, 0.0f), false);
	gameObjects[31] = new Platform(brick, glm::vec3(11.0f, -11.0f, 0.0f), false);
	gameObjects[32] = new Platform(brick, glm::vec3(9.0f, -11.0f, 0.0f), false);
	gameObjects[33] = new Platform(brick, glm::vec3(7.0f, -11.0f, 0.0f), false);
	gameObjects[34] = new Platform(brick, glm::vec3(7.0f, -10.0f, 0.0f), false);
	gameObjects[35] = new Platform(brick, glm::vec3(7.0f, -9.0f, 0.0f), false);
	gameObjects[36] = new Platform(platform, glm::vec3(11.0f, -9.0f, 0.0f), false); ///Final Jump puzzle
	gameObjects[37] = new Platform(brick, glm::vec3(5.0f, -9.0f, 0.0f), false);
	///Level Layout End

	//Player
	Model* playerModel = new Model("SoulKnight.obj", "SoulKnight.mtl", BASE_SHADER);
	Model* swordModel = new Model("KnightSword.obj", "KnightSword.mtl", BASE_SHADER);
	GameObject* sword = new GameObject(swordModel);
	player = new Player(playerModel, sword, /*arrow*/nullptr, glm::vec3(0.0f, 0.0f, 0.0f));

	//Enemy Stuff
	Model* oozeModel = new Model("Ooze.obj", "Ooze.mtl", BASE_SHADER);
	spiker = new Spiker(oozeModel, glm::vec3(2.0f, 0.0f, 0.0f), player);

	Model* flyModel = new Model("DeathFly.obj", "DeathFly.mtl", BASE_SHADER);
	fly = new Fly(flyModel, glm::vec3(-2.0f, 0.0f, 0.0f), player);

	return true;
}

void Scene1::Update(const float deltaTime_)
{
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_W))
	{
		//particleFountain->SetOrigin(particleFountain->GetOrigin() + glm::vec3(0.0f, deltaTime_, 0.0f));
		//Camera::GetInstance()->SetPosition(glm::vec3(Camera::GetInstance()->GetPosition().x, Camera::GetInstance()->GetPosition().y + (deltaTime_ * 4) , Camera::GetInstance()->GetPosition().z));
	}
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_S))
	{
		//particleFountain->SetOrigin(particleFountain->GetOrigin() + glm::vec3(0.0f, -deltaTime_, 0.0f));
		//Camera::GetInstance()->SetPosition(glm::vec3(Camera::GetInstance()->GetPosition().x, Camera::GetInstance()->GetPosition().y - (deltaTime_ * 4), Camera::GetInstance()->GetPosition().z));
	}
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_A))
	{
		//particleFountain->SetOrigin(particleFountain->GetOrigin() + glm::vec3(-deltaTime_, 0.0f, 0.0f));
		//Camera::GetInstance()->SetPosition(glm::vec3(Camera::GetInstance()->GetPosition().x - (deltaTime_ * 4), Camera::GetInstance()->GetPosition().y, Camera::GetInstance()->GetPosition().z));
	}
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_D))
	{
		//particleFountain->SetOrigin(particleFountain->GetOrigin() + glm::vec3(deltaTime_, 0.0f, 0.0f));
		//Camera::GetInstance()->SetPosition(glm::vec3(Camera::GetInstance()->GetPosition().x + (deltaTime_ * 4), Camera::GetInstance()->GetPosition().y, Camera::GetInstance()->GetPosition().z));
	}
	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_1))
	{
		SceneManager::GetInstance()->SetScene(2);
	}

	if (KeyboardInputManager::GetInstance()->KeyPressed(SDL_SCANCODE_F))
	{
		AudioManager::GetInstance()->PlaySoundFX("laserFX");
	}
	if (KeyboardInputManager::GetInstance()->KeyPressed(SDL_SCANCODE_F))
	{
		if (player->GetModel()->GetMesh(0)->iFramesBool == true)
		{
			player->GetModel()->GetMesh(0)->iFramesBool = false;
			player->GetModel()->GetMesh(1)->iFramesBool = false;
		}
		else
		{
			player->GetModel()->GetMesh(0)->iFramesBool = true;
			player->GetModel()->GetMesh(1)->iFramesBool = true;
		}
	}
	player->GetModel()->GetMesh(0)->time += deltaTime_;
	player->GetModel()->GetMesh(1)->time += deltaTime_;

	if (MouseInputManager::GetInstance()->MouseButtonDown(MouseInputManager::back))
	{
		AudioManager::GetInstance()->PlaySoundFX("laserFX");
	}

	/*if (pB != nullptr)
		pB->Update(deltaTime_);*/

	for (int i = 0; i < 5; i++) {
		gameObjects[i]->Update(deltaTime_);
	}

	if (spiker != nullptr) {
		spiker->Update(deltaTime_);
		for (int i = 0; i < 5; i++) {
			spiker->CollisionResponse(gameObjects[i], deltaTime_);
		}
		spiker->CollisionResponse(player->GetAttackBox(), deltaTime_);
		spiker->CollisionResponse(player, deltaTime_);
	}
	
	if (fly != nullptr) {
		fly->Update(deltaTime_);
		
		fly->CollisionResponse(player->GetAttackBox(), deltaTime_);
		fly->CollisionResponse(player, deltaTime_);
	}

	if (player != nullptr) {
		player->Update(deltaTime_);
		for (int i = 0; i < 38; i++) {
			player->PlayerCollision(gameObjects[i], deltaTime_);
		}
		player->PlayerCollision(spiker, deltaTime_);
		player->PlayerCollision(fly, deltaTime_);
		player->PlayerCollision(fly->GetGas(), deltaTime_);
	}

	SceneGraph::GetInstance()->Update(deltaTime_);
}

void Scene1::Render()
{
	//SceneGraph::GetInstance()->Render(Camera::GetInstance());

	spiker->Render(Camera::GetInstance());
	fly->Render(Camera::GetInstance());

	gameObjects[0]->GetModel()->Render(Camera::GetInstance());
	gameObjects[5]->GetModel()->Render(Camera::GetInstance());

	player->Render(Camera::GetInstance());

}