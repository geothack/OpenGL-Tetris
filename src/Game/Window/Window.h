#pragma once

#include <SDL3/SDL.h>

#include <print>
#include <stdexcept>
#include <stacktrace>

class Window
{
public:
	Window(const int width, const int height);
	~Window();


	void Update();

private:
	::SDL_Window* mPlatformWindow;
	::SDL_Event mWindowEvent;
};

