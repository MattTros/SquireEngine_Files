#include "MouseEventListener.h"
#include "../Core/Engine.h"

Engine* MouseEventListener::engineInstance = nullptr;
int MouseEventListener::mouseX = 0;
int MouseEventListener::mouseY = 0;
int MouseEventListener::prevMouseX = 0;
int MouseEventListener::prevMouseY = 0;
bool MouseEventListener::firstUpdate = true;

MouseEventListener::~MouseEventListener()
{
	engineInstance = nullptr;
}

void MouseEventListener::RegisterEngineObject(Engine* engine_)
{
	engineInstance = engine_;
}

void MouseEventListener::Update(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		UpdateMousePosition();
		NotifyMouseDown(e.button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		UpdateMousePosition();
		NotifyMouseUp(e.button.button);
		break;
	case SDL_MOUSEMOTION:
		UpdateMousePosition();
		NotifyMouseMove();
		break;
	case SDL_MOUSEWHEEL:
		NotifyMouseScroll(e.wheel.y);
		break;
	default:
		break;
	}
}

void MouseEventListener::NotifyMouseDown(int buttonType_)
{
	if (engineInstance)
	{
		engineInstance->NotifyMouseDown(mouseX, mouseY);
	}
}

void MouseEventListener::NotifyMouseUp(int buttonType_)
{
	if (engineInstance)
	{
		engineInstance->NotifyMouseUp(mouseX, mouseY, buttonType_);
	}
}

void MouseEventListener::NotifyMouseMove()
{
	if (engineInstance)
	{
		engineInstance->NotifyMouseMove(mouseX, mouseY);
	}
}

void MouseEventListener::NotifyMouseScroll(int y_)
{
	if (engineInstance)
	{
		engineInstance->NotifyMouseScroll(y_);
	}
}

glm::vec2 MouseEventListener::GetPreviousMousePosition()
{
	return glm::vec2(prevMouseX, prevMouseY);
}

glm::vec2 MouseEventListener::GetMousePosition()
{
	return glm::vec2(mouseX, mouseY);
}

glm::vec2 MouseEventListener::GetMouseOffset()
{
	return glm::vec2(mouseX - prevMouseX, prevMouseY - mouseY);
}

void MouseEventListener::UpdateMousePosition()
{
	int tempX, tempY;
	SDL_GetMouseState(&tempX, &tempY);
	tempY = engineInstance->GetScreenSize().y - tempY;
	if (firstUpdate)
	{
		prevMouseX = mouseX = tempX;
		prevMouseY = mouseY = tempY;
		firstUpdate = false;
	}
	else if (tempX != mouseX && tempY != mouseY)
	{
		prevMouseX = mouseX;
		prevMouseY = mouseY;
		mouseX = tempX;
		mouseY = tempY;
	}
}
