#include "GamepadInputManager.h"
#include <iostream>

std::unique_ptr<GamepadInputManager> GamepadInputManager::gamepadInputManagerInstance;

GamepadInputManager::GamepadInputManager()
{
}


GamepadInputManager::~GamepadInputManager()
{
}

GamepadInputManager* GamepadInputManager::GetInstance()
{
	if (gamepadInputManagerInstance.get() == nullptr)
	{
		gamepadInputManagerInstance.reset(new GamepadInputManager);
	}
	return gamepadInputManagerInstance.get();
}

bool GamepadInputManager::ButtonDown(SDL_Scancode scancode_)
{
	return true;
}

void GamepadInputManager::Update()
{
	
}
