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
	Cache->Insert<Material>("TetrisBoard", ::Material({ .Red = 1.0,.Green = 1.0,.Blue = 1.0 }));

	Cache->Insert<OpenGLSprite>("TetrisBoard", ::OpenGLSprite());

	auto xPos = 275;
	auto yPos = 30;

	for (auto i = 0; i < 200; i++)
	{
		if (i % 10 == 0)
		{
			yPos += 25;
			xPos = 275;
		}
		Cache->Insert<Transform>("TetrisBoard" + std::to_string(i), ::Transform(glm::vec2(xPos,yPos), glm::vec2(20)));
		xPos += 25;
	}

	for (auto i = 0; i < 200; i++)
	{
		mTetrisBoard[i] = mMainScene.CreateSpriteEntity(*Cache->Find<Transform>("TetrisBoard"+ std::to_string(i)), *Cache->Find<OpenGLSprite>("TetrisBoard"), *Cache->Find<Material>("TetrisBoard"));
		RuntimeCache->AddEntity(mTetrisBoard[i]);
	}
	
	/*static_cast<Entity&>(mPlayer) = mMainScene.CreateSpriteEntity(*Cache->Find<Transform>("Player"), *Cache->Find<OpenGLSprite>("Player"), *Cache->Find<Material>("Player"));

	RuntimeCache->Add(mPlayer);*/

	mSpriteRenderer = ::OpenGLSpriteRenderer(mMainScene);
}
