#include "Game1.h"

Game1::Game1()
{

}


Game1::~Game1()
{

}

bool Game1::Initialize()
{
	SceneManager::GetInstance()->AddScene(new UIScene, 0);
	SceneManager::GetInstance()->AddScene(new Scene1, 1);
	SceneManager::GetInstance()->AddScene(new Scene2, 2);
	SceneManager::GetInstance()->SetScene(0);
	return true;
}

void Game1::Update(const float deltaTime_)
{
	SceneManager::GetInstance()->Update(deltaTime_);
}

void Game1::Render()
{
	SceneManager::GetInstance()->Render();
}