#ifndef MOUSEINPUTMANAGER_H
#define MOUSEINPUTMANAGER_H

#include <glm/glm.hpp>
#include <SDL.h>
#include <memory>

class MouseInputManager
{
public:
	enum MOUSE_BUTTON
	{
		left = 0,
		right,
		middle,
		back,
		forward
	};
public:
	MouseInputManager(const MouseInputManager&) = delete;
	MouseInputManager(MouseInputManager&&) = delete;
	MouseInputManager& operator = (const MouseInputManager&) = delete;
	MouseInputManager& operator = (MouseInputManager&&) = delete;

	static MouseInputManager* GetInstance();
	bool MouseButtonDown(MOUSE_BUTTON button_);
	bool MouseButtonPressed(MOUSE_BUTTON button_);
	bool MouseButtonReleased(MOUSE_BUTTON button_);
	glm::vec2 MousePosition();
	void Update();
	void UpdatePrevious();
private:
	MouseInputManager();
	~MouseInputManager();
	static std::unique_ptr<MouseInputManager> mouseInputManagerInstance;
	friend std::default_delete<MouseInputManager>;

	Uint32 previousMouseState, mouseState;
	int mouseXPos, mouseYPos;
};

#endif // !MOUSEINPUTMANAGER_H



