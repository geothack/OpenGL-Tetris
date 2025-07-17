#pragma once

#include "Window/Window.h"
#include "Render/Material.h"
#include "Render/OpenGLSpriteRenderer.h"
#include "Render/OpenGLTextRenderer.h"
#include "Render/OpenGLSprite.h"
#include "Render/OpenGLTexture.h"
#include "Render/OpenGLText.h"
#include "WorldTypes/Transform.h"

#include "Gameplay/Player.h"
#include "Gameplay/Block.h"
#include "Gameplay/Ball.h"
#include "Gameplay/LivesText.h"
#include "Gameplay/ScoreText.h"
#include "Gameplay/LevelText.h"
#include "Gameplay/GameController.h"

enum class GameState
{
	None = -1,
	GameStart,
	GameLoop,
	GameEnd
};

class Application
{
public:
	Application();
	~Application();

	void Update();

	inline static GameState GameState = GameState::GameStart;

private:
	void Init();
	void Load();

private:
	::Window mGameWindow;

	::OpenGLSpriteRenderer mSpriteRenderer;

	::OpenGLTextRenderer mTextRenderer;

	// Scenes
	::Scene mMainScene;

	// Player
	Player mPlayer;

	// Ball
	Ball mBall;

	// Texts
	LivesText mLivesText;
	ScoreText mScoreText;
	LevelText mLevelText;

	// StartScreenTexts
	std::array<Entity, 3> mStartScreenTexts;


	// GC
	GameController mGameController;

	// Blocks
	std::array<Block, 30> mBlockArray;

	enum class BlockColor
	{
		None = -1,
		Green,
		Red,
		Blue,
		Yellow,
		Orange,
		Purple
	};


};

