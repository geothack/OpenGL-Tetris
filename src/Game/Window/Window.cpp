#include "Window.h"
#include "Utility/Verify.h"

Window::Window(std::string_view title, const int width, const int height)
{
	auto success = SDL_Init(SDL_INIT_VIDEO);

	Verify::Update("Failed to initialize sdl3. ", success);

	mPlatformWindow = ::SDL_CreateWindow(title.data(), width, height, SDL_WINDOW_OPENGL);

	Verify::Update("Failed to create sdl3 window. ", mPlatformWindow);

	mOpenGLContext = ::SDL_GL_CreateContext(mPlatformWindow);

	auto glSuccess = ::gladLoadGLLoader((GLADloadproc)::SDL_GL_GetProcAddress);

	Verify::Update("Failed to load opengl functions with sdl3. ", glSuccess);

	std::println("OpenGL Loaded with Version {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

	mWindowIsOpen = true;
}

Window::~Window()
{
	::SDL_GL_DestroyContext(mOpenGLContext);
	::SDL_DestroyWindow(mPlatformWindow);
	::SDL_Quit();
}

void Window::Clear() const
{
	::glClearColor(0.8, 0.5, 0.32, 1.0);
	::glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Swap() const
{
	::SDL_GL_SwapWindow(mPlatformWindow);
}

void Window::Events()
{
	while (::SDL_PollEvent(&mWindowEvent))
	{
		if (mWindowEvent.type == ::SDL_EVENT_QUIT)
		{
			mWindowIsOpen = false;
		}
	}
}
