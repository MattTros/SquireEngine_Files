#include "Game1.h"

Game1::Game1()
{

}


Game1::~Game1()
{

}

bool Game1::Initialize()
{
	SceneManager::GetInstance()->SetScene(new UIScene);
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