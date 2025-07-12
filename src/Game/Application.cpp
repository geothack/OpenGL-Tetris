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
	for (auto i = 0; i < 200; i++)
	{
		Cache->Insert<Material>("TetrisBoard" + std::to_string(i), ::Material({.Red = 1.0,.Green = 1.0,.Blue = 1.0}));
	}

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
		mTetrisBoard[i] = mMainScene.CreateSpriteEntity(*Cache->Find<Transform>("TetrisBoard"+ std::to_string(i)), *Cache->Find<OpenGLSprite>("TetrisBoard"), *Cache->Find<Material>("TetrisBoard" + std::to_string(i)));
		RuntimeCache->AddEntity(mTetrisBoard[i]);
	}

	//mTetrisBoard[3].GetComponent<Material>()->UpdateColor({ .Red = 0.25, .Green = 0.34, .Blue = 1.0 });
	//mTetrisBoard[4].GetComponent<Material>()->UpdateColor({ .Red = 0.25, .Green = 0.34, .Blue = 1.0 });
	//mTetrisBoard[5].GetComponent<Material>()->UpdateColor({ .Red = 0.25, .Green = 0.34, .Blue = 1.0 });
	//mTetrisBoard[6].GetComponent<Material>()->UpdateColor({ .Red = 0.25, .Green = 0.34, .Blue = 1.0 });
	
	/*static_cast<Entity&>(mPlayer) = mMainScene.CreateSpriteEntity(*Cache->Find<Transform>("Player"), *Cache->Find<OpenGLSprite>("Player"), *Cache->Find<Material>("Player"));

	RuntimeCache->Add(mPlayer);*/
	std::array<int, 4> lineAlignment;
	for (auto i = 0; i < 4; i++)
	{
		lineAlignment[i] = i;
	}
	mLine = Piece(lineAlignment,{.Red = 0.67, .Green = 0.84, .Blue = 0.9});

	mSpriteRenderer = ::OpenGLSpriteRenderer(mMainScene);
}
