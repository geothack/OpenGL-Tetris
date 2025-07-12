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

	Cache->Insert<OpenGLSprite>("Square", ::OpenGLSprite());

	Cache->Insert<Transform>("Player", ::Transform(glm::vec2(360,550), glm::vec2(80,20)));

	static_cast<Entity&>(mPlayer) = mMainScene.CreateSpriteEntity(*Cache->Find<Transform>("Player"), *Cache->Find<OpenGLSprite>("Square"), *Cache->Find<Material>("Player"));

	RuntimeCache->Add(mPlayer);

	for (auto i = 0; i < 3; i++)
	{
		Cache->Insert<Material>("Block" + std::to_string(i), ::Material({.Red = 0.25, .Green = 0.95, .Blue = 0.23}));
	}
	
	auto xPos = 10;
	auto yPos = 50;
	for (auto i = 0; i < 3; i++)
	{
		Cache->Insert<Transform>("Block" + std::to_string(i), ::Transform(glm::vec2(xPos, yPos), glm::vec2(60, 30)));
		xPos += 80;
	}

	for (auto i = 0; i < 3; i++)
	{
		static_cast<Entity&>(mBlockArray[i]) = mMainScene.CreateSpriteEntity(*Cache->Find<Transform>("Block" + std::to_string(i)), *Cache->Find<OpenGLSprite>("Square"), *Cache->Find<Material>("Block" + std::to_string(i)));

		RuntimeCache->Add(mBlockArray[i]);
	}


	mSpriteRenderer = ::OpenGLSpriteRenderer(mMainScene);
}
