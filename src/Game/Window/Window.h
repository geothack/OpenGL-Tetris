#pragma once


class Window
{
public:
	Window() = default;
	Window(std::string_view title, const int width, const int height);
	~Window();

	Window(const Window&) = delete;
	Window& operator=(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&&) = delete;

	void Swap() const;

	void Events();

public:
	inline const bool const GetWindowIsOpen() const { return mWindowIsOpen; }
	bool SetWindowIsOpen(bool value) { return mWindowIsOpen = value; }

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

