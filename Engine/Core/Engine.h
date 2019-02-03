#ifndef ENGINE_H
#define ENGINE_H

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100

#include "Window.h"
#include "Timer.h"
#include "GameInterface.h"
#include "../Graphics/Shader.h"
#include "../Camera/Camera.h"
#include "../Graphics/TextureHandler.h"
#include "../Rendering/3D/GameObject.h"
#include "../Events/EventListener.h"
#include "../Rendering/SceneGraph.h"
#include "../FX/AudioManager.h"
#include "../Events/KeyboardInputManager.h"
#include "../Events/GamepadInputManager.h"
#include "../Graphics/ParticleSystem.h"
#include "../UI/UIManager.h"
#include <memory>

class Engine
{
public:
	Engine(const Engine&) = delete;
	Engine(Engine&&) = delete;
	Engine& operator = (const Engine&) = delete;
	Engine& operator = (Engine&&) = delete;

	bool Initialize(std::string name_, int width_, int height_);
	void Run();
	bool GetIsRunning();
	static Engine* GetInstance();
	void SetGameInterface(GameInterface* gameInterface_);

	glm::vec2 GetScreenSize() const;

	void NotifyMouseDown(int x_, int y_);
	void NotifyMouseUp(int x_, int y_, int buttonType_);
	void NotifyMouseMove(int x_, int y_);
	void NotifyMouseScroll(int y_);

	void NotifyButtonDown(int state_, int type_);
	void NotifyButtonUp(int state_, int type_);
	void NotifyButtonADown();
	void NotifyButtonAUp();
	void NotifyButtonBDown();
	void NotifyButtonBUp();
	void NotifyButtonXDown();
	void NotifyButtonXUp();
	void NotifyButtonYDown();
	void NotifyButtonYUp();

	Window* GetWindow() const;

	void ExitGame();
private:
	Engine();
	~Engine();
	void Update(const float deltaTime_);
	void Render();
	void ShutDown();

	static std::unique_ptr<Engine> engineInstance;
	friend std::default_delete<Engine>;

	Window* window;
	Timer timer;
	GameInterface* gameInterface;
	bool isRunning;
	unsigned int fps;
};

#endif // !ENGINE_H



