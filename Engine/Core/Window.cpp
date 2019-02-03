#include "Window.h"



Window::Window()
{
	window = nullptr;
}


Window::~Window()
{
	ShutDown();
}

bool Window::Initialize(std::string name_, int width_, int height_)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0)
	{
		std::cout << "Failed to initialize SDL" << std::endl;
		Debug::FatalError("Failed to initialize SDL", __FILE__, __LINE__);
		return false;
	}
	width = width_;
	height = height_;

	window = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (!window)
	{
		std::cout << "Failed to create window" << std::endl;
		Debug::FatalError("Failed to create window", __FILE__, __LINE__);
		return false;
	}

	context = SDL_GL_CreateContext(window);
	SetAttributes();

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "Glew initialization failed" << std::endl;
		Debug::FatalError("Glew initialization failed", __FILE__, __LINE__);
		return false;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, width, height);

	Debug::Info("OpenGL version: " + std::string((char*)glGetString(GL_VERSION)), __FILE__, __LINE__);
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	return true;
}

void Window::ShutDown()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::GetHeight()
{
	return height;
}

int Window::GetWidth()
{
	return width;
}

SDL_Window* Window::GetWindow() const
{
	return window;
}

SDL_GLContext Window::GetContext() const {
	return context;
}

void Window::SetAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;
}
