#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
//#include <stdio.h>
#include <string>
#include <iostream>

#include "Debug.h"

#define GL3_PROTOTYPES 1

class Window
{
public:
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator = (const Window&) = delete;
	Window& operator = (Window&&) = delete;

	Window();
	~Window();
	bool Initialize(std::string name_, int width_, int height_);
	void ShutDown();
	int GetHeight();
	int GetWidth();
	void SetHeight(int height_);
	void SetWidth(int width);
	SDL_Window* GetWindow() const;
	SDL_GLContext GetContext() const;
private:
	void SetAttributes();
	int height;
	int width;
	SDL_Window* window;
	SDL_GLContext context;
};

#endif // !WINDOW_H



