#pragma once

#include <print>

#include "Window/Window.h"

class Application
{
public:
	Application();
	~Application();

	void Update();

private:
	::Window mGameWindow;
};

