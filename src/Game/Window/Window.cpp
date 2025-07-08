#include "Window.h"

Window::Window(std::string_view title, const int width, const int height)
{
	auto success = SDL_Init(SDL_INIT_VIDEO);

	Verify::Update("Failed to initialize sdl3. ", success);

	mPlatformWindow = ::SDL_CreateWindow(title.data(), width, height, SDL_WINDOW_OPENGL);

	Verify::Update("Failed to create sdl3 window. ", mPlatformWindow);

	mWindowIsOpen = true;
}

Window::~Window()
{
	SDL_DestroyWindow(mPlatformWindow);
	SDL_Quit();
}

void Window::Update()
{
}

void Window::Events()
{
	while (SDL_PollEvent(&mWindowEvent))
	{
		if (mWindowEvent.type == SDL_EVENT_QUIT)
		{
			mWindowIsOpen = false;
		}
	}
}
