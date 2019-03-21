#include "Scene2.h"
#include "SceneManager.h"

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

	//AudioManager::GetInstance()->LoadSoundFXFile("laserFX", "Laser.wav");

	CollisionHandler::GetInstance()->Initialize(100.0f);

	Model* platform = new Model("Platform.obj", "Platform.mtl", BASE_SHADER);
	Model* brick = new Model("Brick.obj", "Brick.mtl", BASE_SHADER);

	gameObjects[0] = new Platform(brick, glm::vec3(0.0f, -2.0f, 0.0f), false);
	gameObjects[1] = new Platform(brick, glm::vec3(2.0f, -2.0f, 0.0f), false);
	gameObjects[2] = new Platform(brick, glm::vec3(4.0f, -2.0f, 0.0f), false);
	gameObjects[3] = new Platform(brick, glm::vec3(5.0f, -3.0f, 0.0f), false);
	gameObjects[4] = new Platform(brick, glm::vec3(6.0f, -4.0f, 0.0f), false);
	gameObjects[5] = new Platform(brick, glm::vec3(8.0f, -4.0f, 0.0f), false);
	gameObjects[6] = new Platform(brick, glm::vec3(10.0f, -4.0f, 0.0f), false);///Enemy 1 Spawn
	gameObjects[7] = new Platform(brick, glm::vec3(12.0f, -4.0f, 0.0f), false);
	gameObjects[8] = new Platform(brick, glm::vec3(13.0f, -3.0f, 0.0f), false);
	gameObjects[9] = new Platform(brick, glm::vec3(14.0f, -2.0f, 0.0f), false);
	gameObjects[10] = new Platform(brick, glm::vec3(16.0f, -2.0f, 0.0f), false);
	gameObjects[11] = new Platform(brick, glm::vec3(18.0f, -2.0f, 0.0f), false);
	gameObjects[12] = new Platform(brick, glm::vec3(20.0f, -2.0f, 0.0f), false);
	gameObjects[13] = new Platform(brick, glm::vec3(21.0f, -3.0f, 0.0f), false);
	gameObjects[14] = new Platform(brick, glm::vec3(22.0f, -4.0f, 0.0f), false);
	gameObjects[15] = new Platform(brick, glm::vec3(24.0f, -4.0f, 0.0f), false);
	gameObjects[16] = new Platform(brick, glm::vec3(26.0f, -4.0f, 0.0f), false);///Enemy 2 Spawn
	gameObjects[17] = new Platform(brick, glm::vec3(28.0f, -4.0f, 0.0f), false);
	gameObjects[18] = new Platform(brick, glm::vec3(29.0f, -3.0f, 0.0f), false);
	gameObjects[19] = new Platform(brick, glm::vec3(30.0f, -2.0f, 0.0f), false);
	gameObjects[20] = new Platform(brick, glm::vec3(32.0f, -2.0f, 0.0f), false);

	gameObjects[21] = new Wall(brick, glm::vec3(5.0f, -3.0f, 0.0f), false);///Walls for Ooze
	gameObjects[22] = new Wall(brick, glm::vec3(13.0f, -3.0f, 0.0f), false);
	
	Model* hitBox = new Model("AttackBox.obj", "AttackBox.mtl", BASE_SHADER);
	end = new Flag(hitBox, glm::vec3(32.0f, -1.0f, 0.0f), 1);

	//Player
	Model* playerModel = new Model("SoulKnight.obj", "SoulKnight.mtl", BASE_SHADER);
	Model* swordModel = new Model("KnightSword.obj", "KnightSword.mtl", BASE_SHADER);
	GameObject* sword = new GameObject(swordModel);
	player = new Player(playerModel, sword, /*arrow*/nullptr, glm::vec3(0.0f, -1.0f, 0.0f));

	//Enemy Stuff
	Model* oozeModel = new Model("Ooze.obj", "Ooze.mtl", BASE_SHADER);
	ooze = new Ooze(oozeModel, glm::vec3(10.0f, -3.0f, 0.0f), true, player);

	Model* flyModel = new Model("DeathFly.obj", "DeathFly.mtl", BASE_SHADER);
	fly = new Fly(flyModel, glm::vec3(26.0f, -3.0f, 0.0f), player);

	return true;
}

void Scene2::Update(const float deltaTime_)
{
	//SceneGraph::GetInstance()->Update(deltaTime_);

	for (int i = 0; i < 23; i++) {
		gameObjects[i]->Update(deltaTime_);
	}

	if (ooze != nullptr) {
		ooze->Update(deltaTime_);
		for (int i = 0; i < 23; i++) {
			ooze->CollisionResponse(gameObjects[i], deltaTime_);
		}
		ooze->CollisionResponse(player->GetAttackBox(), deltaTime_);
		ooze->CollisionResponse(player, deltaTime_);
	}

	/*if (fly != nullptr) {
		fly->Update(deltaTime_);

		fly->CollisionResponse(player->GetSword(), deltaTime_);
		fly->CollisionResponse(player, deltaTime_);
	}*/

	if (player != nullptr) {
		player->Update(deltaTime_);
		for (int i = 0; i < 23; i++) {
			player->PlayerCollision(gameObjects[i], deltaTime_);
		}
		player->PlayerCollision(ooze, deltaTime_);
	}

	if (end != nullptr)
	{
		end->OnCollision(player);
	}
}

void Scene2::Render()
{
	//SceneGraph::GetInstance()->Render(Camera::GetInstance());

	ooze->GetModel()->Render(Camera::GetInstance());
	fly->GetModel()->Render(Camera::GetInstance());

	player->Render(Camera::GetInstance());

	gameObjects[0]->GetModel()->Render(Camera::GetInstance());
}