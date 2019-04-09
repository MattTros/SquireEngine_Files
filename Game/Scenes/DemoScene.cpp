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

	CollisionHandler::GetInstance()->Initialize(100.0f);

	AudioManager::GetInstance()->StopAudioChannel(0);

	//Initialization Area
	Model* model = new Model("Apple.obj", "Apple.mtl", BASE_SHADER);
	testOBJ = new GameObject(model, glm::vec3(10.0f));
	//End of Initialization Area

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
		ChangeState();
		timer = 0.0f;
	}
	UpdateState(deltaTime_);
}

void DemoScene::Render()
{
	switch (state)
	{
	case 0:
		//Audio Manager
		testOBJ->GetModel()->Render(Camera::GetInstance());
		break;
	case 1:
		//OBJ loader
		testOBJ->GetModel()->Render(Camera::GetInstance());
		break;
	case 2:
		//Materials
		break;
	case 3:
		//Input managers
		break;
	case 4:
		//Lighting
		break;
	case 5:
		//Shader
		break;
	case 6:
		//Physics
		break;
	case 7:
		//Collision
		break;
	case 8:
		//UI
		break;
	case 9:
		//Textures
		break;
	case 10:
		//Options
		break;
	case 11:
		//Particles
		break;
	case 12:
		//Parallaxing Background
		break;
	case 13:
		//Player
		break;
	case 14:
		//AI & Enemies
		break;
	case 15:
		//Combat
		break;
	case 16:
		//IFrames
		break;
	}
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
		//Player
		State_Player();
		break;
	case 14:
		//AI & Enemies
		State_AIEnemies();
		break;
	case 15:
		//Combat
		State_Combat();
		break;
	case 16:
		//IFrames
		State_IFrames();
		break;
	}
}

void DemoScene::UpdateState(float deltaTime_)
{
	switch (state)
	{
	case 0:
		//Audio Manager
		testOBJ->Update(deltaTime_);
		break;
	case 1:
		//OBJ loader
		testOBJ->Update(deltaTime_);
		break;
	case 2:
		//Materials
		break;
	case 3:
		//Input managers
		break;
	case 4:
		//Lighting
		break;
	case 5:
		//Shader
		break;
	case 6:
		//Physics
		break;
	case 7:
		//Collision
		break;
	case 8:
		//UI
		break;
	case 9:
		//Textures
		break;
	case 10:
		//Options
		break;
	case 11:
		//Particles
		break;
	case 12:
		//Parallaxing Background
		break;
	case 13:
		//Player
		break;
	case 14:
		//AI & Enemies
		break;
	case 15:
		//Combat
		break;
	case 16:
		//IFrames
		break;
	}
}

void DemoScene::State_AudioManager()
{
	testOBJ->SetPosition(glm::vec3(0.0f));
}

void DemoScene::State_OBJLoader()
{
	testOBJ->SetPosition(glm::vec3(1.0f));
}

void DemoScene::State_Materials()
{

}

void DemoScene::State_InputManagers()
{

}

void DemoScene::State_Lighting()
{

}

void DemoScene::State_Shader()
{

}

void DemoScene::State_Physics()
{

}

void DemoScene::State_Collision()
{

}

void DemoScene::State_UI()
{

}

void DemoScene::State_Textures()
{

}

void DemoScene::State_Options()
{

}

void DemoScene::State_Particles()
{

}

void DemoScene::State_ParallaxingBackground()
{

}

void DemoScene::State_Player()
{

}

void DemoScene::State_AIEnemies()
{

}

void DemoScene::State_Combat()
{

}

void DemoScene::State_IFrames()
{

}