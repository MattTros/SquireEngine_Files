#include "Engine.h"

std::unique_ptr<Engine> Engine::engineInstance;

Engine::Engine()
{
	window = nullptr;
	gameInterface = nullptr;
	isRunning = false;
	fps = 60;
}


Engine::~Engine()
{

}

bool Engine::Initialize(std::string name_, int width_, int height_)
{
	Debug::DebugInit();
	Debug::SetSeverity(MessageType::TYPE_INFO);

	window = new Window();
	if (!window->Initialize("Engine Window", 1600, 900))
	{
		Debug::FatalError("Failed to initialize window", __FILE__, __LINE__);
		std::cout << "Failed to initialize window" << std::endl;
		return isRunning = false;
	}

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);
	MouseEventListener::RegisterEngineObject(this);

	Shader::GetInstance()->CreateProgram("colorShader", "Engine/Shaders/ColorVertexShader.glsl", "Engine/Shaders/ColorFragmentShader.glsl");
	Shader::GetInstance()->CreateProgram("baseShader", "Engine/Shaders/VertexShader.glsl", "Engine/Shaders/FragmentShader.glsl");

	if (gameInterface)
	{
		if (!gameInterface->Initialize())
		{
			Debug::FatalError("Failed to initialize game interface", __FILE__, __LINE__);
			std::cout << "Failed to initialize game interface" << std::endl;
			return isRunning = false;
		}
	}

	timer.Start();

	Debug::Info("Initialization succesful", __FILE__, __LINE__);

	return isRunning = true;
}

void Engine::Run()
{
	while (isRunning)
	{
		KeyboardInputManager::GetInstance()->Update();
		GamepadInputManager::GetInstance()->Update();
		EventListener::Update();
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}

	if (!isRunning)
	{
		ShutDown();
	}
}

bool Engine::GetIsRunning()
{
	return isRunning;
}

Engine* Engine::GetInstance()
{
	if (engineInstance.get() == nullptr)
	{
		engineInstance.reset(new Engine);
	}
	return engineInstance.get();
}

Window* Engine::GetWindow() const {
	return window;
}

void Engine::SetGameInterface(GameInterface* gameInterface_)
{
	gameInterface = gameInterface_;
}

glm::vec2 Engine::GetScreenSize() const
{
	return glm::vec2(window->GetWidth(), window->GetHeight());
}

///Mouse Input
void Engine::NotifyMouseDown(int x_, int y_)
{
	std::cout << "Click Down" << std::endl;
}

void Engine::NotifyMouseUp(int x_, int y_, int buttonType_)
{
	std::cout << "Click Up" << std::endl;
	CollisionHandler::GetInstance()->Update(glm::vec2(x_, y_), buttonType_);
}

void Engine::NotifyMouseMove(int x_, int y_)
{
	//Uncomment to enable mouse-camera movement
	//Camera::GetInstance()->ProcessMouseMovement(MouseEventListener::GetMouseOffset().x, MouseEventListener::GetMouseOffset().y);
}

void Engine::NotifyMouseScroll(int y_)
{
	//Uncomment to enable mouse-camera zooming
	//Camera::GetInstance()->ProcessMouseZoom(y_);
}

///Controller Input
void Engine::NotifyButtonDown(int state_, int type_)
{
	std::cout << "Button Down: " << type_ << std::endl;
}

void Engine::NotifyButtonUp(int state_, int type_)
{

}

void Engine::NotifyButtonADown()
{

}

void Engine::NotifyButtonAUp()
{

}

void Engine::NotifyButtonBDown()
{

}

void Engine::NotifyButtonBUp()
{

}

void Engine::NotifyButtonXDown()
{

}

void Engine::NotifyButtonXUp()
{

}

void Engine::NotifyButtonYDown()
{

}

void Engine::NotifyButtonYUp()
{

}

float Engine::Randomize(float min_, float max_)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max_ - min_;
	float r = random * diff;
	return min_ + r;
}

void Engine::ExitGame()
{
	isRunning = false;
}

void Engine::Update(const float deltaTime_)
{
	if (gameInterface)
	{
		gameInterface->Update(deltaTime_);
	}
}

void Engine::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (gameInterface)
	{
		gameInterface->Render();
	}

	SDL_GL_SwapWindow(window->GetWindow());
}

void Engine::ShutDown()
{
	delete window;
	window = nullptr;
	delete gameInterface;
	gameInterface = nullptr;

	SDL_Quit();

	exit(0);
}
