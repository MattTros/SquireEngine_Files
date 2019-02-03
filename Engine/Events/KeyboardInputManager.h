#ifndef KEYBOARDINPUTMANAGER_H
#define KEYBOARDINPUTMANAGER_H

#include <SDL.h>
#include <memory>

class KeyboardInputManager
{
public:
	KeyboardInputManager(const KeyboardInputManager&) = delete;
	KeyboardInputManager(KeyboardInputManager&&) = delete;
	KeyboardInputManager& operator = (const KeyboardInputManager&) = delete;
	KeyboardInputManager& operator = (KeyboardInputManager&&) = delete;

	static KeyboardInputManager* GetInstance();
	bool KeyDown(SDL_Scancode scancode_);
	void Update();
	
private:
	KeyboardInputManager();
	~KeyboardInputManager();

	static std::unique_ptr<KeyboardInputManager> keyboardInputManagerInstance;
	friend std::default_delete<KeyboardInputManager>;
	const Uint8* keyboardStates;
};


#endif // !KEYBOARDINPUTMANAGER_H


