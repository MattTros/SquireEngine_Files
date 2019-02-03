#ifndef GAMEPADINPUTMANAGER_H
#define GAMEPADINPUTMANAGER_H

#include <SDL.h>
#include <memory>

class GamepadInputManager
{
public:
	GamepadInputManager(const GamepadInputManager&) = delete;
	GamepadInputManager(GamepadInputManager&&) = delete;
	GamepadInputManager& operator = (const GamepadInputManager&) = delete;
	GamepadInputManager& operator = (GamepadInputManager&&) = delete;
	
	static GamepadInputManager* GetInstance();
	bool ButtonDown(SDL_Scancode scancode_);
	void Update();
private:
	GamepadInputManager();
	~GamepadInputManager();

	static std::unique_ptr<GamepadInputManager> gamepadInputManagerInstance;
	friend std::default_delete<GamepadInputManager>;
	const Uint8* controllerStates;
};


#endif // !GAMEPADINPUTMANAGER_H


