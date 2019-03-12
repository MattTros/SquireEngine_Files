#include "Scene1.h"
#include "SceneManager.h"

Scene1::Scene1() {

}
Scene1::~Scene1() {

}

bool Scene1::Initialize()
{
	std::string texturePath = "Resources/Textures/";

	Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.7f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f)));
	TextureHandler::GetInstance()->CreateTexture("playdrunnerTexture", texturePath + "PlaydRunnerLogoCircleCircuit.png");

	AudioManager::GetInstance()->LoadSoundFXFile("laserFX", "Laser.wav");

	CollisionHandler::GetInstance()->Initialize(100.0f);

	//Model* apple = new Model("Apple.obj", "Apple.mtl", BASE_SHADER);
	Model* dice = new Model("Dice.obj", "Dice.mtl", BASE_SHADER);
	go = new GameObject(dice, glm::vec3(0.0f));
	//! Create background images:
	//pB = new ParallaxingBackground();
	//pB->Initialize();

	/*particleFountain = new ParticleSystem();
	particleFountain->CreateSystem(dice, 100, glm::vec3(0.05f), glm::vec3(1.0f), glm::vec3(-0.5f, 0.0f, 0.0f), glm::vec3(-0.75f, 0.0f, 0.0f), 1.0f, 2.0f);
	particleFountain->SetOrigin(glm::vec3(0));
	particleFountain->SetGravity(0.0f);
	particleFountain->SetRotationSpeed(5.0f);
	particleFountain->StartSystem();*/

	///Level Layout Start
	Model* platform = new Model("Platform.obj", "Platform.mtl", BASE_SHADER);
	Model* brick = new Model("Brick.obj", "Brick.mtl", BASE_SHADER);

	platforms[0] = new Platform(brick, glm::vec3(0.0f, -2.0f, 0.0f), false);
	platforms[1] = new Platform(brick, glm::vec3(2.0f, -2.0f, 0.0f), false);
	platforms[2] = new Platform(brick, glm::vec3(-2.0f, -2.0f, 0.0f), false);
	platforms[3] = new Platform(brick, glm::vec3(4.0f, -2.0f, 0.0f), false);
	platforms[4] = new Platform(brick, glm::vec3(6.0f, -2.0f, 0.0f), false);
	platforms[5] = new Platform(platform, glm::vec3(10.0f, -2.0f, 0.0f), false);
	platforms[6] = new Platform(brick, glm::vec3(7.0f, -3.0f, 0.0f), false);
	platforms[7] = new Platform(brick, glm::vec3(8.0f, -4.0f, 0.0f), false);
	platforms[8] = new Platform(brick, glm::vec3(10.0f, -4.0f, 0.0f), false);
	platforms[9] = new Platform(brick, glm::vec3(12.0f, -4.0f, 0.0f), false);
	platforms[10] = new Platform(brick, glm::vec3(14.0f, -4.0f, 0.0f), false);
	platforms[11] = new Platform(brick, glm::vec3(14.0f, -3.0f, 0.0f), false);
	platforms[12] = new Platform(brick, glm::vec3(14.0f, -2.0f, 0.0f), false);
	platforms[13] = new Platform(brick, glm::vec3(16.0f, -2.0f, 0.0f), false);
	platforms[14] = new Platform(brick, glm::vec3(18.0f, -2.0f, 0.0f), false);
	platforms[15] = new Platform(platform, glm::vec3(20.0f, -2.0f, 0.0f), false);
	platforms[16] = new Platform(brick, glm::vec3(22.0f, -2.0f, 0.0f), false);
	platforms[17] = new Platform(brick, glm::vec3(22.0f, -1.0f, 0.0f), false);
	platforms[18] = new Platform(brick, glm::vec3(22.0f, 0.0f, 0.0f), false);
	platforms[19] = new Platform(brick, glm::vec3(22.0f, -3.0f, 0.0f), false);
	platforms[20] = new Platform(brick, glm::vec3(22.0f, -4.0f, 0.0f), false);
	platforms[21] = new Platform(brick, glm::vec3(22.0f, -5.0f, 0.0f), false);
	platforms[22] = new Platform(brick, glm::vec3(22.0f, -6.0f, 0.0f), false);
	platforms[23] = new Platform(brick, glm::vec3(20.0f, -6.0f, 0.0f), false);
	platforms[24] = new Platform(brick, glm::vec3(19.0f, -7.0f, 0.0f), false);
	platforms[25] = new Platform(brick, glm::vec3(18.0f, -8.0f, 0.0f), false);
	platforms[26] = new Platform(brick, glm::vec3(17.0f, -9.0f, 0.0f), false);
	platforms[27] = new Platform(brick, glm::vec3(15.0f, -9.0f, 0.0f), false);
	platforms[28] = new Platform(brick, glm::vec3(15.0f, -10.0f, 0.0f), false);
	platforms[29] = new Platform(brick, glm::vec3(15.0f, -11.0f, 0.0f), false);
	platforms[30] = new Platform(brick, glm::vec3(13.0f, -11.0f, 0.0f), false);
	platforms[31] = new Platform(brick, glm::vec3(11.0f, -11.0f, 0.0f), false);
	platforms[32] = new Platform(brick, glm::vec3(9.0f, -11.0f, 0.0f), false);
	platforms[33] = new Platform(brick, glm::vec3(7.0f, -11.0f, 0.0f), false);
	platforms[34] = new Platform(brick, glm::vec3(7.0f, -10.0f, 0.0f), false);
	platforms[35] = new Platform(brick, glm::vec3(7.0f, -9.0f, 0.0f), false);
	platforms[36] = new Platform(platform, glm::vec3(11.0f, -9.0f, 0.0f), false);
	platforms[37] = new Platform(brick, glm::vec3(5.0f, -9.0f, 0.0f), false);
	///Level Layout End

	//Player
	Model* playerModel = new Model("SoulKnight.obj", "SoulKnight.mtl", BASE_SHADER);
	player = new Player(playerModel, /*sword*/nullptr, /*arrow*/nullptr, glm::vec3(0.0f, 5.0f, 0.0f));

	//Enemy Stuff
	//Model* oozeModel = new Model("Ooze.obj", "Ooze.mtl", BASE_SHADER);
	//ooze = new Ooze(oozeModel, glm::vec3(0.0f, 0.0f, 0.0f), true , player);

	return true;
}

void Scene1::Update(const float deltaTime_)
{
	//go->Update(deltaTime_);
	/*if (particleFountain != nullptr)
		particleFountain->Update(deltaTime_);*/

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
		SceneManager::GetInstance()->SetScene(new Scene2);
	}

	if (KeyboardInputManager::GetInstance()->KeyDown(SDL_SCANCODE_F))
	{
		AudioManager::GetInstance()->PlaySoundFX("laserFX");
	}

	/*if (pB != nullptr)
		pB->Update(deltaTime_);*/

	for (int i = 0; i < 5; i++) {
		platforms[i]->Update(deltaTime_);
	}

	/*if (ooze != nullptr) {
		ooze->Update(deltaTime_);
		for (int i = 0; i < 5; i++) {
			ooze->CollisionResponse(platforms[i], deltaTime_);
		}
	}*/

	if (player != nullptr) {
		player->Update(deltaTime_);
		for (int i = 0; i < 38; i++) {
			player->GroundCollision(platforms[i], deltaTime_);
		}
	}

	SceneGraph::GetInstance()->Update(deltaTime_);
}

void Scene1::Render()
{
	//go->GetModel()->Render(Camera::GetInstance());
	//SceneGraph::GetInstance()->Render(Camera::GetInstance());
	/*if (particleFountain != nullptr)
		particleFountain->Render(Camera::GetInstance());*/

	//ooze->GetModel()->Render(Camera::GetInstance());

	player->Render(Camera::GetInstance());

	//for (int i = 0; i < 3; i++) {
	platforms[0]->GetModel()->Render(Camera::GetInstance());
	platforms[5]->GetModel()->Render(Camera::GetInstance());
	//}

}