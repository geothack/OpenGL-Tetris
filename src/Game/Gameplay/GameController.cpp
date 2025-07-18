#include "Utility/PreLibrary.h"
#include "GameController.h"
#include "Utility/ResourceCache.h"
#include "Render/OpenGLTexture.h"
#include "Render/OpenGLShader.h"

GameController::GameController(std::span<Block, 30> blocks, Ball& ball, Player& player) : mBall(&ball), mPlayer(&player)
{
	if (blocks.size() != 30)
	{
		Verify::Update("Span must have exactly 30 elements.", 0);
	}
	std::copy(blocks.begin(), blocks.end(), mGameBlocks.begin());
}

GameController::~GameController()
{
}

void GameController::BeginPlay()
{

	//SetBlockPositions(10);
	
}

void GameController::Update()
{
	if (Shake)
	{
		ShakeScreen();

		if (mCounter % 30 == 0)
		{
			mTimer += 0.025f;
		}

		if (mTimer >= 2)
		{
			mCounter = 0;
			mTimer = 0.0f;
			Shake = false;
		}
	}


	// Lv2
	if (GameScore == 100)
	{
		SetBlockPositions(20);
		GameScore += 10;
		GameLevel++;
		mBall->HasShot = false;
		mBall->SetBallStartShotDirection();
		if (GameLevel % 2 == 0)
		{
			GameLives++;
		}
	}
	// Lv3
	if (GameScore == 310)
	{
		SetBlockPositions(30);
		GameScore += 10;
		GameLevel++;
		mBall->HasShot = false;
		mBall->SetBallStartShotDirection();
	}
	// Lv4
	if (GameScore == 620)
	{
		SetBlockPositions(30);
		GameScore += 10;
		GameLevel++;
		mBall->HasShot = false;
		mBall->SetBallStartShotDirection();
		mBall->BallTimeStep--;
		if (GameLevel % 2 == 0)
		{
			GameLives++;
		}
	}
	// Lv5
	if (GameScore == 930)
	{
		SetBlockPositions(30);
		GameScore += 10;
		GameLevel++;
		mBall->HasShot = false;
		mBall->SetBallStartShotDirection();
		mPlayer->SetEntitySize(glm::vec2(80, 20));
		Player::PlayerSpeed = 2;
		mPrevLevelScore = GameScore;
	}
	// Lv6 -- Infinite Loop Mechanic 
	if (GameScore == mPrevLevelScore + 300)
	{
		if (GameLevel % 2 == 0)
		{
			GameLives++;
		}

		SetBlockPositions(30);
		GameScore += 10;
		GameLevel++;
		mBall->HasShot = false;
		mBall->SetBallStartShotDirection();
		mPrevLevelScore = GameScore;
	}
}

void GameController::SetBlockPositions(const int amount)
{
	auto xPos = 10;
	auto yPos = -40;
	for (auto i = 0; i < amount; i++)
	{
		if (i % 10 == 0)
		{
			xPos = 10;
			yPos += 50;
		}
		mGameBlocks[i].GetComponent<Transform>()->UpdatePosition(glm::vec2(xPos, yPos));
		xPos += 80;
	}
}

void GameController::ShakeScreen()
{
	mCounter += 2;
	Cache->Find<OpenGLShader>("ShakeScreen")->Attach();
	Cache->Find<OpenGLShader>("ShakeScreen")->SetFloat("time", mTimer);
}
