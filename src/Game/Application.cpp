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

		EntityRuntimeCache::Get()->Update();
       
		mGameWindow.Swap();
	}

	mPlayerSprite.Free();
	EntityRuntimeCache::Get()->Free();
}

void Application::Init()
{
    mSquareMaterial = ::Material({ .Red = 0.23,.Green = 0.79,.Blue = 0.67 });

	mPlayerSprite = ::OpenGLSprite();

	mPlayerTransform = ::Transform(glm::vec2(100),glm::vec2(100));

	Entity& playerEntity = mPlayer;

	playerEntity = mMainScene.CreateEntity(mPlayerTransform);
	playerEntity.AddComponent<OpenGLSprite>(mPlayerSprite);
	playerEntity.AddComponent<Material>(mSquareMaterial);

	EntityRuntimeCache::Get()->Add(playerEntity);

	mSpriteRenderer = ::OpenGLSpriteRenderer(mPlayer);
}
