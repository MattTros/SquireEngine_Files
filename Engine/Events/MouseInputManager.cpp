#include "MouseInputManager.h"

std::unique_ptr<MouseInputManager> MouseInputManager::mouseInputManagerInstance = nullptr;

MouseInputManager::MouseInputManager()
{
}


MouseInputManager::~MouseInputManager()
{
}

MouseInputManager* MouseInputManager::GetInstance()
{
	if (mouseInputManagerInstance.get() == nullptr)
	{
		mouseInputManagerInstance.reset(new MouseInputManager);
	}
	return mouseInputManagerInstance.get();
}

bool MouseInputManager::MouseButtonDown(MOUSE_BUTTON button_)
{
	Uint32 mask = 0;

	switch (button_)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;
	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	case middle:
		mask = SDL_BUTTON_MMASK;
		break;
	case back:
		mask = SDL_BUTTON_X1MASK;
		break;
	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}
	return(mouseState & mask);
}

bool MouseInputManager::MouseButtonPressed(MOUSE_BUTTON button_)
{
	Uint32 mask = 0;

	switch (button_)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;
	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	case middle:
		mask = SDL_BUTTON_MMASK;
		break;
	case back:
		mask = SDL_BUTTON_X1MASK;
		break;
	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}
	return !(previousMouseState & mask) && (mouseState & mask);
}

bool MouseInputManager::MouseButtonReleased(MOUSE_BUTTON button_)
{
	Uint32 mask = 0;

	switch (button_)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;
	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	case middle:
		mask = SDL_BUTTON_MMASK;
		break;
	case back:
		mask = SDL_BUTTON_X1MASK;
		break;
	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}
	return (previousMouseState & mask) && !(mouseState & mask);
}

glm::vec2 MouseInputManager::MousePosition()
{
	return glm::vec2((float)mouseXPos, (float)mouseYPos);
}

void MouseInputManager::Update()
{
	mouseState = SDL_GetMouseState(&mouseXPos, &mouseYPos);
}

void MouseInputManager::UpdatePrevious()
{
	previousMouseState = mouseState;
}
