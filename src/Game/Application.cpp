#include "Application.h"

Application::Application() : mGameWindow(Window("Tetris",800,600))
{
	Update();
}

Application::~Application()
{
}

void Application::Update()
{
	while (mGameWindow.GetWindowIsOpen())
	{
		mGameWindow.Events();
	}
}
