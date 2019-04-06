#include "Scene1.h"
#include "SceneManager.h"

Scene1::Scene1() {

}
Scene1::~Scene1() {

}

bool Scene1::Initialize()
{

	Camera::GetInstance()->SetPosition(glm::vec3(0.0f, 0.0f, 3.15f));
	Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.7f, 0.7f, glm::vec3(1.0f, 1.0f, 1.0f)));

	CollisionHandler::GetInstance()->Initialize(100.0f);

	AudioManager::GetInstance()->StopAudioChannel(0);

	///Level Layout Start
	Model* platform = new Model("Platform.obj", "Platform.mtl", BASE_SHADER);
	Model* brick = new Model("Brick.obj", "Brick.mtl", BASE_SHADER);
	Model* spike = new Model("Spike.obj", "Spike.mtl", BASE_SHADER);

	gameObjects[0] = new Platform(brick, glm::vec3(0.0f, -2.0f, 0.0f), false); //Movement tutorial here
	gameObjects[1] = new Platform(brick, glm::vec3(2.0f, -2.0f, 0.0f), false);
	gameObjects[2] = new Platform(brick, glm::vec3(-2.0f, -2.0f, 0.0f), false);
	gameObjects[3] = new Platform(brick, glm::vec3(4.0f, -2.0f, 0.0f), false);
	gameObjects[4] = new Platform(brick, glm::vec3(6.0f, -2.0f, 0.0f), false); //Jump tutorial here
	gameObjects[5] = new Platform(brick, glm::vec3(10.0f, -2.0f, 0.0f), false); ///First jump puzzle
	gameObjects[6] = new Platform(brick, glm::vec3(6.0f, -3.0f, 0.0f), false);
	gameObjects[7] = new Platform(brick, glm::vec3(7.0f, -4.0f, 0.0f), false);
	gameObjects[8] = new Platform(brick, glm::vec3(9.0f, -4.0f, 0.0f), false);
	gameObjects[9] = new Platform(brick, glm::vec3(11.0f, -4.0f, 0.0f), false);
	gameObjects[10] = new Platform(brick, glm::vec3(13.0f, -4.0f, 0.0f), false);
	gameObjects[11] = new Platform(brick, glm::vec3(14.0f, -3.0f, 0.0f), false);
	gameObjects[12] = new Platform(brick, glm::vec3(14.0f, -2.0f, 0.0f), false);
	gameObjects[13] = new Platform(brick, glm::vec3(16.0f, -2.0f, 0.0f), false);
	gameObjects[14] = new Platform(brick, glm::vec3(18.0f, -2.0f, 0.0f), false);
	gameObjects[15] = new DropThroughPlatform(platform, glm::vec3(20.0f, -2.0f, 0.0f), false); ///Drop through platform
	gameObjects[16] = new Platform(brick, glm::vec3(22.0f, -2.0f, 0.0f), false);
	gameObjects[17] = new Platform(brick, glm::vec3(22.0f, -1.0f, 0.0f), false);
	gameObjects[18] = new Platform(brick, glm::vec3(22.0f, 0.0f, 0.0f), false);
	gameObjects[41] = new Platform(brick, glm::vec3(22.0f, 1.0f, 0.0f), false);
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
	gameObjects[36] = new Platform(brick, glm::vec3(11.0f, -9.0f, 0.0f), false); ///Final Jump puzzle
	gameObjects[37] = new Platform(brick, glm::vec3(5.0f, -9.0f, 0.0f), false);
	gameObjects[38] = new Spike(spike, glm::vec3(13.0f, -10.5f, 0.0f), false); //Spike
	gameObjects[39] = new Spike(spike, glm::vec3(11.0f, -10.5f, 0.0f), false); //Spike
	gameObjects[40] = new Spike(spike, glm::vec3(9.0f, -10.5, 0.0f), false); //Spike
	gameObjects[42] = new Spike(spike, glm::vec3(21.0f, 0.0f, 0.0f), false); //Spike
	gameObjects[43] = new Spike(spike, glm::vec3(21.0f, 1.0f, 0.0f), false); //Spike

	gameObjects[42]->SetRotation(glm::vec3(0.0f, 0.0f, 1.0f));
	gameObjects[42]->SetAngle(1.575);
	gameObjects[43]->SetRotation(glm::vec3(0.0f, 0.0f, 1.0f));
	gameObjects[43]->SetAngle(1.575);
	///Level Layout End

	Model* hitBox = new Model("AttackBox.obj", "AttackBox.mtl", BASE_SHADER);
	end = new Flag(hitBox, glm::vec3(5.0f, -8.0f, 0.0f), 2);

	//Player
	Model* playerModel = new Model("SoulKnight.obj", "SoulKnight.mtl", BASE_SHADER);
	Model* swordModel = new Model("KnightSword.obj", "KnightSword.mtl", BASE_SHADER);
	GameObject* sword = new GameObject(swordModel);
	player = new Player(playerModel, sword, glm::vec3(0.0f, -1.0f, 0.0f));

	//! Create background images:
	pB = new ParallaxingBackground(player);
	pB->Initialize();

	AudioManager::GetInstance()->PlaySoundFX("introAndWalkJumpTutorial");

	movementTutorial = new TutorialCollider("Movement", glm::vec3(0.0f, -1.0f, 0.0f));	
	expositionCollider = new TutorialCollider("Exposition", glm::vec3(2.0f, -1.0f, 0.0f));	
	jumpTutorial = new TutorialCollider("Jump", glm::vec3(6.0f, -1.0f, 0.0f));
	dropTutorial = new TutorialCollider("Drop", glm::vec3(20.0f, -1.0f, 0.0f));

	initTimer = WaitForSeconds();
	initTimer.waitTime = 4.0f;
	initTimer.seconds = 0.0f;
	initTimer.active = true;
	player->SetGravity(false);

	return true;
}

void Scene1::Update(const float deltaTime_)
{
	if (initTimer.active)
	{
		initTimer.seconds += deltaTime_;
		if (initTimer.seconds >= initTimer.waitTime)
		{
			initTimer.active = false;
			player->SetGravity(true); 
			initTimer.seconds = 0.0f;
		}
	}

	if (pB != nullptr)
		pB->Update(deltaTime_);

	for (int i = 0; i < 44; i++) {
		gameObjects[i]->Update(deltaTime_);
	}

	if (player != nullptr) {
		player->Update(deltaTime_);
		for (int i = 0; i < 44; i++) {
			player->PlayerCollision(gameObjects[i], deltaTime_);
		}
		player->PlayerCollision(movementTutorial, deltaTime_);
		player->PlayerCollision(jumpTutorial, deltaTime_);
		player->PlayerCollision(dropTutorial, deltaTime_);
		player->PlayerCollision(expositionCollider, deltaTime_);
		if (player->arrow != nullptr)
		{
			for (int i = 0; i < 44; i++)
			{
				if (player->arrow->ProjectileColliding(player->arrow, gameObjects[i]))
				{
					player->arrow->SetLifetime(2.0f);
				}
			}
		}
		if (player->GetPosition().y < -11)
		{
			SceneManager::GetInstance()->SetScene(SceneManager::GetInstance()->GetSceneIndex());
		}
	}

	if (end != nullptr)
	{
		end->Update(deltaTime_);
		end->OnCollision(player);
	}

	SceneGraph::GetInstance()->Update(deltaTime_);
}

void Scene1::Render()
{
	//SceneGraph::GetInstance()->Render(Camera::GetInstance());

	gameObjects[0]->GetModel()->Render(Camera::GetInstance());
	gameObjects[15]->GetModel()->Render(Camera::GetInstance());
	gameObjects[38]->GetModel()->Render(Camera::GetInstance());

	pB->Render(Camera::GetInstance());

	end->Render(Camera::GetInstance());

	player->Render(Camera::GetInstance());

}