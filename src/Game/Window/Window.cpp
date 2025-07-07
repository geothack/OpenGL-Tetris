#include "Window.h"

Window::Window(const int width, const int height)
{
	auto success = SDL_Init(SDL_INIT_VIDEO);

	if (success == 0)
	{
		throw std::runtime_error("Failed to initialize sdl3.");
	}
}

Window::~Window()
{
}

void Window::Update()
{
}
