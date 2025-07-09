#pragma once

#include "Window/Window.h"
#include "Render/Material.h"

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

	// Materials
	::Material mSquareMaterial;

	::uint32_t VAO;
};

