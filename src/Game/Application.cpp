#include "Utility/PreLibrary.h"
#include "Application.h"
#include "Utility/EntityRuntimeCache.h"
#include "Utility/ResourceCache.h"
#include "Utility/RendererCache.h"

Application::Application() : mGameWindow(Window("Breakout",800,600))
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

		GRenderer->Update();

		RuntimeCache->Update();

		mGameWindow.Swap();
	}

	for (auto& sprite : Cache->FindEntireMap<OpenGLSprite>())
	{
		sprite.second.Free();
	}
	GRenderer->Free();
	RuntimeCache->Free();
	Cache->Free();
}

void Application::Init()
{
	mPlayer = Player(mBall);
	Cache->Insert<Material>("Player", ::Material({ .Red = 0.25, .Green = 0.35, .Blue = 1.0 }));

	Cache->Insert<OpenGLSprite>("Square", ::OpenGLSprite());

	Cache->Insert<Transform>("Player", ::Transform(glm::vec2(340,550), glm::vec2(120,20)));

	static_cast<Entity&>(mPlayer) = mMainScene.CreateSpriteEntity(*Cache->Find<Transform>("Player"), *Cache->Find<OpenGLSprite>("Square"), *Cache->Find<Material>("Player"));

	RuntimeCache->Add(mPlayer);

	auto color = 0;

	for (auto i = 0; i < 6; i++)
	{
		switch ((BlockColor)color)
		{
			using enum BlockColor;
		case Green:
			Cache->Insert<Material>("Block" + std::to_string(i), ::Material({ .Red = 0.25, .Green = 0.95, .Blue = 0.23 }));
			break;
		case Red:
			Cache->Insert<Material>("Block" + std::to_string(i), ::Material({ .Red = 1.0, .Green = 0.0, .Blue = 0.0 }));
			break;
		case Blue:
			Cache->Insert<Material>("Block" + std::to_string(i), ::Material({ .Red = 0.0, .Green = 0.0, .Blue = 1.0 }));
			break;
		case Yellow:
			Cache->Insert<Material>("Block" + std::to_string(i), ::Material({ .Red = 0.85, .Green = 0.68, .Blue = 0.23 }));
			break;
		case Orange:
			Cache->Insert<Material>("Block" + std::to_string(i), ::Material({ .Red = 1.0, .Green = 0.0, .Blue = 1.0 }));
			break;
		case Purple:
			Cache->Insert<Material>("Block" + std::to_string(i), ::Material({ .Red = 1.0, .Green = 1.0, .Blue = 0.0 }));
			break;
		}
		color++;
	}
	color = 0;

	auto xPos = 10;
	auto yPos = -40;
	for (auto i = 0; i < 30; i++)
	{
		if (i % 10 == 0)
		{
			xPos = 10;
			yPos += 50;
		}
		Cache->Insert<Transform>("Block" + std::to_string(i), ::Transform(glm::vec2(xPos, yPos), glm::vec2(60, 30)));
		xPos += 80;
	}

	for (auto i = 0; i < 30; i++)
	{
		if (color >= 6)
		{
			color = 0;
		}
		static_cast<Entity&>(mBlockArray[i]) = mMainScene.CreateSpriteEntity(*Cache->Find<Transform>("Block" + std::to_string(i)), *Cache->Find<OpenGLSprite>("Square"), *Cache->Find<Material>("Block" + std::to_string(color)));

		RuntimeCache->Add(mBlockArray[i]);
		color++;
	}

	mBall = Ball(static_cast<Entity&>(mPlayer), mBlockArray);

	Cache->Insert<Transform>("Ball", ::Transform(glm::vec2(385,500),glm::vec2(30)));
	Cache->Insert<OpenGLTexture>("Ball", ::OpenGLTexture("res/Textures/circle.png"));
	Cache->Insert<OpenGLShader>("Ball", ::OpenGLShader("res/Shaders/SpriteTextured.vert", "res/Shaders/SpriteTextured.frag"));

	static_cast<Entity&>(mBall) = mMainScene.CreateShaderSpriteEntity(*Cache->Find<Transform>("Ball"), *Cache->Find<OpenGLSprite>("Square"), *Cache->Find<OpenGLShader>("Ball"));
	mBall.AddComponent<OpenGLTexture>(*Cache->Find<OpenGLTexture>("Ball"));

	RuntimeCache->Add(mBall);

	// Text

	Cache->Insert<OpenGLShader>("Text", OpenGLShader("res/Shaders/Text.vert","res/Shaders/Text.frag"));

	Cache->Insert<OpenGLText>("Lives", OpenGLText(35, "LIVES   " + std::to_string(GameController::GameLives), {.X = 70,.Y = 1,.Scale = 1.0f,.Color = glm::vec3(1.0)}, *Cache->Find<OpenGLShader>("Text")));

	Cache->Find<OpenGLText>("Lives")->LoadFont("res/Fonts/Frohburg.ttf");

	static_cast<Entity&>(mLivesText) = mMainScene.CreateTextEntity(*Cache->Find<OpenGLText>("Lives"), *Cache->Find<OpenGLShader>("Text"));

	RuntimeCache->Add(mLivesText);


	Cache->Insert<OpenGLText>("Score", OpenGLText(35, "Score   " + std::to_string(GameController::GameLives), { .X = 620,.Y = 1,.Scale = 1.0f,.Color = glm::vec3(1.0) }, *Cache->Find<OpenGLShader>("Text")));

	Cache->Find<OpenGLText>("Score")->LoadFont("res/Fonts/Frohburg.ttf");

	static_cast<Entity&>(mScoreText) = mMainScene.CreateTextEntity(*Cache->Find<OpenGLText>("Score"), *Cache->Find<OpenGLShader>("Text"));

	RuntimeCache->Add(mScoreText);


	Cache->Insert<OpenGLText>("Level", OpenGLText(35, "Level   " + std::to_string(GameController::GameLevel), { .X = 345,.Y = 1,.Scale = 1.0f,.Color = glm::vec3(1.0) }, *Cache->Find<OpenGLShader>("Text")));

	Cache->Find<OpenGLText>("Level")->LoadFont("res/Fonts/Frohburg.ttf");

	static_cast<Entity&>(mLevelText) = mMainScene.CreateTextEntity(*Cache->Find<OpenGLText>("Level"), *Cache->Find<OpenGLShader>("Text"));

	RuntimeCache->Add(mLevelText);



	Cache->Insert<Transform>("GC",Transform());

	mGameController = GameController();

	static_cast<Entity&>(mGameController) = mMainScene.CreateEntity(*Cache->Find<Transform>("GC"));

	RuntimeCache->Add(mGameController);

	mTextRenderer = ::OpenGLTextRenderer(mMainScene);

	mSpriteRenderer = ::OpenGLSpriteRenderer(mMainScene);

	GRenderer->Add(mSpriteRenderer, 0);
	GRenderer->Add(mTextRenderer, 1);
}
