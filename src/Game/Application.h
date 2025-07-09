#pragma once

#include <print>

#include "Window/Window.h"
#include "Render/OpenGLShader.h"

class Application
{
public:
	Application();
	~Application();

	void Update();

private:
	void Init();


private:
	::Window mGameWindow;

	// Shaders
	::OpenGLShader mBasicShader;

	uint32_t VAO;
};

