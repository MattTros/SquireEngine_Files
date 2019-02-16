#include "Game1.h"

Game1::Game1()
{

}


Game1::~Game1()
{
	
}

bool Game1::Initialize()
{
	scene = new Scene1();
	scene->Initialize();


	return true;
}

void Game1::Update(const float deltaTime_)
{
	scene->Update(deltaTime_);
}

void Game1::Render()
{

	scene->Render();
}

void Game1::SetScene(SceneManager* newScene_) {
	scene = newScene_;
}
