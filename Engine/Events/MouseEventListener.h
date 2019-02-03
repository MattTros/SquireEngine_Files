#ifndef MOUSEEVENTLISTENER_H
#define MOUSEEVENTLISTENER_H

#include <SDL.h>
#include <glm/glm.hpp>

class Engine;

class MouseEventListener
{
public:
	MouseEventListener(const MouseEventListener&) = delete;
	MouseEventListener(MouseEventListener&&) = delete;
	MouseEventListener& operator = (const MouseEventListener&) = delete;
	MouseEventListener& operator = (MouseEventListener&&) = delete;

	MouseEventListener() = delete;
	~MouseEventListener();

	static void RegisterEngineObject(Engine* engine_);
	static void Update(SDL_Event e);
	static void NotifyMouseDown(int buttonType_);
	static void NotifyMouseUp(int buttonType_);
	static void NotifyMouseMove();
	static void NotifyMouseScroll(int y_);
	static glm::vec2 GetPreviousMousePosition();
	static glm::vec2 GetMousePosition();
	static glm::vec2 GetMouseOffset();
private:
	static Engine* engineInstance;
	static int mouseX, mouseY, prevMouseX, prevMouseY;
	static bool firstUpdate;

	static void UpdateMousePosition();
};

#endif // !MOUSEEVENTLISTENER_H

