#include "Utility/PreLibrary.h"
#include "Application.h"
#include "Utility/EntityRuntimeCache.h"

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

		RuntimeCache->Update();
       
		mGameWindow.Swap();
	}

	mPlayerSprite.Free();
	RuntimeCache->Free();
}

void Application::Init()
{
    mSquareMaterial = ::Material({ .Red = 0.23,.Green = 0.79,.Blue = 0.67 });

	mPlayerSprite = ::OpenGLSprite();

	mPlayerTransform = ::Transform(glm::vec2(100),glm::vec2(100));

	
	static_cast<Entity&>(mPlayer) = mMainScene.CreateEntity(mPlayerTransform);
	mPlayer.AddComponent<OpenGLSprite>(mPlayerSprite);
	mPlayer.AddComponent<Material>(mSquareMaterial);

	RuntimeCache->Add(mPlayer);

	mSpriteRenderer = ::OpenGLSpriteRenderer(mPlayer);
}
