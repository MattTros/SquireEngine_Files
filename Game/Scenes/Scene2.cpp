#include "Scene2.h"

Scene2::Scene2() {

}
Scene2::~Scene2() {

}

bool Scene2::Initialize()
{
	std::string texturePath = "Resources/Textures/";

	Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.7f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f)));
	TextureHandler::GetInstance()->CreateTexture("playdrunnerTexture", texturePath + "PlaydRunnerLogoCircleCircuit.png");

	AudioManager::GetInstance()->LoadSoundFXFile("laserFX", "Laser.wav");

	CollisionHandler::GetInstance()->Initialize(100.0f);

	Model* apple = new Model("Apple.obj", "Apple.mtl", BASE_SHADER);
	Model* dice = new Model("Dice.obj", "Dice.mtl", BASE_SHADER);

	//! Create background images:
	pB = new ParallaxingBackground();
	pB->Initialize();

	particleFountain = new ParticleSystem();
	particleFountain->CreateSystem(dice, 20, glm::vec3(0.05f), glm::vec3(2.0f), glm::vec3(-0.5f, 0.0f, 0.0f), glm::vec3(-0.75f, 0.0f, 0.0f), 1.0f, 2.0f);
	particleFountain->SetOrigin(glm::vec3(0));
	particleFountain->SetGravity(0.0f);
	particleFountain->SetRotationSpeed(5.0f);
	particleFountain->StartSystem();

	Model* brick = new Model("Brick.obj", "Brick.mtl", BASE_SHADER);

	glm::vec3 pos1 = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 pos2 = glm::vec3(0.0f, -2.0f, 0.0f);

	p = new Platform(brick, pos2, false);
	p2 = new Platform(brick, pos1,  true);

	return true;
}

void Scene2::Update(const float deltaTime_)
{
	if (particleFountain != nullptr)
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

	if (pB != nullptr)
		pB->Update(deltaTime_);

	if (p != nullptr)
		p->Update(deltaTime_);

	if (p2 != nullptr)
		p2->Update(deltaTime_);

		p->onCollision(p2);
		p2->onCollision(p);

	SceneGraph::GetInstance()->Update(deltaTime_);
}

void Scene2::Render()
{
	SceneGraph::GetInstance()->Render(Camera::GetInstance());
	if (particleFountain != nullptr)
		particleFountain->Render(Camera::GetInstance());

	if (p != nullptr)
		p->GetModel()->Render(Camera::GetInstance());

	if (p2 != nullptr) {
		p2->GetModel()->Render(Camera::GetInstance());
	}
}