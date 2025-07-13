#include "Utility/PreLibrary.h"
#include "Window.h"
#include "Utility/Verify.h"
#include "Input/Input.h"

Window::Window(std::string_view title, const int width, const int height)
{
	auto success = SDL_Init(SDL_INIT_VIDEO);

	Verify::Update("Failed to initialize sdl3. ", success);

	// Set to use Render Doc!!!
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	mPlatformWindow = ::SDL_CreateWindow(title.data(), width, height, SDL_WINDOW_OPENGL);

	Verify::Update("Failed to create sdl3 window. ", mPlatformWindow);

	mOpenGLContext = ::SDL_GL_CreateContext(mPlatformWindow);

	auto glSuccess = ::gladLoadGLLoader((GLADloadproc)::SDL_GL_GetProcAddress);

	Verify::Update("Failed to load opengl functions with sdl3. ", glSuccess);

	std::println("OpenGL Loaded with Version {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(DebugLog, nullptr);

	mWindowIsOpen = true;
}

Window::~Window()
{
	::SDL_GL_DestroyContext(mOpenGLContext);
	::SDL_DestroyWindow(mPlatformWindow);
	::SDL_Quit();
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

		GInput->UpdateKeys();
	}
}

void Window::DebugLog(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		std::println("OpenGL Debug Severity High {}", message);
		break;

	case GL_DEBUG_SEVERITY_MEDIUM:
		std::println("OpenGL Debug Severity Medium {}", message);
		break;

	case GL_DEBUG_SEVERITY_LOW:
		std::println("OpenGL Debug Severity Low {}", message);
		break;

	case GL_DEBUG_SEVERITY_NOTIFICATION:
		std::println("OpenGL Debug Severity Notification {}", message);
		break;

	default:

		break;
	}
}
