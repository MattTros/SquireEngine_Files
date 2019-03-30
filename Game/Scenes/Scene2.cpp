#include "Scene2.h"
#include "SceneManager.h"

Scene2::Scene2() {

}
Scene2::~Scene2() {

}

bool Scene2::Initialize()
{
	Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.7f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f)));

	//AudioManager::GetInstance()->LoadSoundFXFile("laserFX", "Laser.wav");

	CollisionHandler::GetInstance()->Initialize(100.0f);

	Model* platform = new Model("Platform.obj", "Platform.mtl", BASE_SHADER);
	Model* brick = new Model("Brick.obj", "Brick.mtl", BASE_SHADER);

	gameObjects[0] = new Platform(brick, glm::vec3(0.0f, -2.0f, 0.0f), false);
	gameObjects[1] = new Platform(brick, glm::vec3(2.0f, -2.0f, 0.0f), false);
	gameObjects[2] = new Platform(brick, glm::vec3(4.0f, -2.0f, 0.0f), false); //Sword tutorial
	gameObjects[3] = new Platform(brick, glm::vec3(5.0f, -3.0f, 0.0f), false);//wall
	gameObjects[4] = new Platform(brick, glm::vec3(6.0f, -4.0f, 0.0f), false);
	gameObjects[5] = new Platform(brick, glm::vec3(8.0f, -4.0f, 0.0f), false);
	gameObjects[6] = new Platform(brick, glm::vec3(10.0f, -4.0f, 0.0f), false);///Enemy 1 Spawn
	gameObjects[7] = new Platform(brick, glm::vec3(12.0f, -4.0f, 0.0f), false);
	gameObjects[8] = new Platform(brick, glm::vec3(13.0f, -3.0f, 0.0f), false);//wall
	gameObjects[9] = new Platform(brick, glm::vec3(14.0f, -2.0f, 0.0f), false);
	gameObjects[10] = new Platform(brick, glm::vec3(16.0f, -2.0f, 0.0f), false);
	gameObjects[11] = new Platform(brick, glm::vec3(18.0f, -2.0f, 0.0f), false);
	gameObjects[12] = new Platform(brick, glm::vec3(20.0f, -2.0f, 0.0f), false); //Dash tutorial
	gameObjects[13] = new Platform(brick, glm::vec3(21.0f, -3.0f, 0.0f), false);
	gameObjects[14] = new Platform(brick, glm::vec3(22.0f, -4.0f, 0.0f), false);
	gameObjects[15] = new Platform(brick, glm::vec3(24.0f, -4.0f, 0.0f), false);
	gameObjects[16] = new Platform(brick, glm::vec3(26.0f, -4.0f, 0.0f), false);///Enemy 2 Spawn
	gameObjects[17] = new Platform(brick, glm::vec3(28.0f, -4.0f, 0.0f), false);
	gameObjects[18] = new Platform(brick, glm::vec3(29.0f, -3.0f, 0.0f), false);
	gameObjects[19] = new Platform(brick, glm::vec3(30.0f, -2.0f, 0.0f), false);
	gameObjects[20] = new Platform(brick, glm::vec3(32.0f, -2.0f, 0.0f), false); //Projectile tutorial
	gameObjects[23] = new Platform(brick, glm::vec3(33.0f, -3.0f, 0.0f), false);//wall
	gameObjects[24] = new Platform(brick, glm::vec3(34.0f, -4.0f, 0.0f), false);
	gameObjects[25] = new Platform(brick, glm::vec3(36.0f, -4.0f, 0.0f), false);
	gameObjects[26] = new Platform(brick, glm::vec3(38.0f, -4.0f, 0.0f), false);///Enemy 3 Spawn
	gameObjects[27] = new Platform(brick, glm::vec3(40.0f, -4.0f, 0.0f), false);
	gameObjects[28] = new Platform(brick, glm::vec3(41.0f, -3.0f, 0.0f), false);//wall
	gameObjects[29] = new Platform(brick, glm::vec3(42.0f, -2.0f, 0.0f), false);
	gameObjects[30] = new Platform(brick, glm::vec3(44.0f, -2.0f, 0.0f), false);

	gameObjects[21] = new Wall(brick, glm::vec3(5.0f, -3.0f, 0.0f), false);///Walls for Ooze
	gameObjects[22] = new Wall(brick, glm::vec3(13.0f, -3.0f, 0.0f), false);
	
	gameObjects[31] = new Wall(brick, glm::vec3(33.0f, -3.0f, 0.0f), false);///Walls for Spiker
	gameObjects[32] = new Wall(brick, glm::vec3(41.0f, -3.0f, 0.0f), false);

	Model* hitBox = new Model("AttackBox.obj", "AttackBox.mtl", BASE_SHADER);
	end = new Flag(hitBox, glm::vec3(44.0f, -1.0f, 0.0f), 0);

	//Player
	Model* playerModel = new Model("SoulKnight.obj", "SoulKnight.mtl", BASE_SHADER);
	Model* swordModel = new Model("KnightSword.obj", "KnightSword.mtl", BASE_SHADER);
	GameObject* sword = new GameObject(swordModel);
	player = new Player(playerModel, sword, glm::vec3(0.0f, -1.0f, 0.0f));

	//Enemy Stuff
	Model* oozeModel = new Model("Ooze.obj", "Ooze.mtl", BASE_SHADER);
	ooze = new Ooze(oozeModel, glm::vec3(10.0f, -3.0f, 0.0f), true, player);

	Model* flyModel = new Model("DeathFly.obj", "DeathFly.mtl", BASE_SHADER);
	fly = new Fly(flyModel, glm::vec3(26.0f, -3.0f, 0.0f), player);

	Model* spikerModel = new Model("Spiker.obj", "Spiker.mtl", BASE_SHADER);
	spiker = new Spiker(spikerModel, glm::vec3(38.0f, -3.0f, 0.0f), player);

	swordTutorial = new TutorialCollider("SwordAttack", glm::vec3(4.0f, -1.0f, 0.0f));
	dashTutorial = new TutorialCollider("Dash", glm::vec3(20.0f, -1.0f, 0.0f));
	arrowTutorial = new TutorialCollider("Arrow", glm::vec3(32.0f, -1.0f, 0.0f));

	pB = new ParallaxingBackground();
	pB->Initialize();

	initTimer = WaitForSeconds();
	initTimer.waitTime = 4.0f;
	initTimer.seconds = 0.0f;
	initTimer.active = true;
	player->SetGravity(false); ooze->SetGravity(false); spiker->SetGravity(false);

	return true;
}

void Scene2::Update(const float deltaTime_)
{
	//SceneGraph::GetInstance()->Update(deltaTime_);

	if (initTimer.active)
	{
		initTimer.seconds += deltaTime_;
		if (initTimer.seconds >= initTimer.waitTime)
		{
			initTimer.active = false;
			player->SetGravity(true); ooze->SetGravity(true); spiker->SetGravity(true);
			initTimer.seconds = 0.0f;
		}
	}

	for (int i = 0; i < 33; i++) {
		gameObjects[i]->Update(deltaTime_);
	}

	if (ooze != nullptr) {
		ooze->Update(deltaTime_);
		for (int i = 0; i < 33; i++) {
			ooze->CollisionResponse(gameObjects[i], deltaTime_);
		}
		ooze->CollisionResponse(player->GetAttackBox(), deltaTime_);
		ooze->CollisionResponse(player, deltaTime_);
		if (player->arrow != nullptr)
			ooze->CollisionResponse(player->arrow, deltaTime_);
		if (ooze->GetHealth() <= 0) {
			ooze->~Ooze();
			ooze = nullptr;
		}
	}

	if (spiker != nullptr) {
		spiker->Update(deltaTime_);
		for (int i = 0; i < 33; i++) {
			spiker->CollisionResponse(gameObjects[i], deltaTime_);
		}
		spiker->CollisionResponse(player->GetAttackBox(), deltaTime_);
		spiker->CollisionResponse(player, deltaTime_);
		if (player->arrow != nullptr)
			spiker->CollisionResponse(player->arrow, deltaTime_);
		if (spiker->GetHealth() <= 0) {
			spiker->~Spiker();
			spiker = nullptr;
		}
	}

	if (fly != nullptr) {
		fly->Update(deltaTime_);

		fly->CollisionResponse(player->GetAttackBox(), deltaTime_);
		fly->CollisionResponse(player, deltaTime_);
		if (player->arrow != nullptr)
			fly->CollisionResponse(player->arrow, deltaTime_);
		if (fly->GetHealth() <= 0) {
			fly->~Fly();
			fly = nullptr;
		}
	}

	if (player != nullptr) {
		player->Update(deltaTime_);
		for (int i = 0; i < 33; i++) {
			player->PlayerCollision(gameObjects[i], deltaTime_);
		}
		if (ooze != nullptr)
			player->PlayerCollision(ooze, deltaTime_);
		if (fly != nullptr) {
			player->PlayerCollision(fly, deltaTime_);
			player->PlayerCollision(fly->GetGas(), deltaTime_);
		}
		if (spiker != nullptr) {
			player->PlayerCollision(spiker, deltaTime_);
			if (spiker->shotSpike != nullptr)
				player->PlayerCollision(spiker->shotSpike, deltaTime_);
		}
		player->PlayerCollision(swordTutorial, deltaTime_);
		player->PlayerCollision(dashTutorial, deltaTime_);
		player->PlayerCollision(arrowTutorial, deltaTime_);
	}

	pB->Update(deltaTime_);

	if (end != nullptr)
	{
		end->Update(deltaTime_);
		end->OnCollision(player);
	}
}

void Scene2::Render()
{
	//SceneGraph::GetInstance()->Render(Camera::GetInstance());
	pB->Render(Camera::GetInstance());

	if(ooze != nullptr)
		ooze->Render(Camera::GetInstance());

	if (fly != nullptr)
		fly->Render(Camera::GetInstance());

	if (spiker != nullptr)
		spiker->Render(Camera::GetInstance());

	gameObjects[0]->GetModel()->Render(Camera::GetInstance());

	end->Render(Camera::GetInstance());

	player->Render(Camera::GetInstance());
}