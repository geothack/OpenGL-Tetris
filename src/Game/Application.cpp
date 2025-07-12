#include "Utility/PreLibrary.h"
#include "Application.h"
#include "Utility/EntityRuntimeCache.h"
#include "Utility/ResourceCache.h"

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

	for (auto& sprite : Cache->FindEntireMap<OpenGLSprite>())
	{
		sprite.second.Free();
	}
	RuntimeCache->Free();
	Cache->Free();
}

void Application::Init()
{

	Cache->Insert<Material>("Player", ::Material({ .Red = 0.25, .Green = 0.35, .Blue = 1.0 }));
	
	Cache->Insert<OpenGLSprite>("Player", ::OpenGLSprite());

	Cache->Insert<Transform>("Player", ::Transform(glm::vec2(360,550), glm::vec2(80,20)));

	static_cast<Entity&>(mPlayer) = mMainScene.CreateSpriteEntity(*Cache->Find<Transform>("Player"), *Cache->Find<OpenGLSprite>("Player"), *Cache->Find<Material>("Player"));

	RuntimeCache->Add(mPlayer);


	mSpriteRenderer = ::OpenGLSpriteRenderer(mMainScene);
}
