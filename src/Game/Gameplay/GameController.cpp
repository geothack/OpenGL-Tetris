#include "Utility/PreLibrary.h"
#include "GameController.h"

GameController::GameController(std::span<Block, 30> blocks, Ball& ball) : mBall(&ball)
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
	using enum Level;
	if (mGameLevel == Lv1)
	{
		SetBlockPositions(10);
	}
}

void GameController::Update()
{
	if (GameScore == 100)
	{
		SetBlockPositions(20);
		GameScore += 10;
		GameLevel++;
		mBall->HasShot = false;
		mBall->SetBallStartShotDirection();
	}

	if (GameScore == 310)
	{
		SetBlockPositions(30);
		GameScore += 10;
		GameLevel++;
		mBall->HasShot = false;
		mBall->SetBallStartShotDirection();
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
