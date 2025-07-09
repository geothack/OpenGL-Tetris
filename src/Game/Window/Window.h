#pragma once
#include <glad/glad.h>
#include <SDL3/SDL.h>

#include <string_view>

class Window
{
public:
	Window() = default;
	Window(std::string_view title, const int width, const int height);
	~Window();

	void Clear() const;

	void Swap() const;

	void Events();

public:
	inline const bool const GetWindowIsOpen() const { return mWindowIsOpen; }

private:
	::SDL_Window* mPlatformWindow;
	::SDL_Event mWindowEvent;
	::SDL_GLContext mOpenGLContext;

	bool mWindowIsOpen = false;
};

