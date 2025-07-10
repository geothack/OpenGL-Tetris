#pragma once


class Window
{
public:
	Window() = default;
	Window(std::string_view title, const int width, const int height);
	~Window();

	void Swap() const;

	void Events();

public:
	inline const bool const GetWindowIsOpen() const { return mWindowIsOpen; }

private:
	static void APIENTRY DebugLog(GLenum source,
		GLenum type,
		unsigned int id,
		GLenum severity,
		GLsizei length,
		const char* message,
		const void* userParam);
	
private:
	::SDL_Window* mPlatformWindow;
	::SDL_Event mWindowEvent;
	::SDL_GLContext mOpenGLContext;

	bool mWindowIsOpen = false;
};

