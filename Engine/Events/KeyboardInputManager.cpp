#include "KeyboardInputManager.h"

std::unique_ptr<KeyboardInputManager> KeyboardInputManager::keyboardInputManagerInstance = nullptr;

KeyboardInputManager::KeyboardInputManager()
{

}


KeyboardInputManager::~KeyboardInputManager()
{
}

KeyboardInputManager* KeyboardInputManager::GetInstance()
{
	if (keyboardInputManagerInstance.get() == nullptr)
	{
		keyboardInputManagerInstance.reset(new KeyboardInputManager);
	}
	return keyboardInputManagerInstance.get();
}

bool KeyboardInputManager::KeyDown(SDL_Scancode scancode_)
{
	return keyboardStates[scancode_];
}

void KeyboardInputManager::Update()
{
	keyboardStates = SDL_GetKeyboardState(NULL);
}
