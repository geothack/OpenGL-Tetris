#include "Utility/PreLibrary.h"
#include "Application.h"

Application::Application() : mGameWindow(Window("Tetris",800,600))
{
	Init();
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

		mSpriteRenderer.Update();

		mPlayerSprite.DrawSprite(glm::vec2(200),glm::vec2(200),45.0f);
        

		mGameWindow.Swap();
	}
}

void Application::Init()
{
    mSquareMaterial = ::Material({ .Red = 0.23,.Green = 0.79,.Blue = 0.67 });

	mPlayerSprite = ::OpenGLSprite(mSquareMaterial);

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800),static_cast<float>(600), 0.0f, -1.0f, 1.0f);

	mSquareMaterial.SetMat4("projection", projection);
}
