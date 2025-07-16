#include "Utility/PreLibrary.h"
#include "Ball.h"
#include "Utility/ResourceCache.h"
#include "Utility/Helper.h"
#include "Gameplay/GameController.h"
#include "Utility/Verify.h"

Ball::Ball(Entity& player, std::span<Block> blocks) : mPlayer(&player)
{
	if (blocks.size() != 30)
	{
		Verify::Update("Span must have exactly 30 elements.",0);
	}
	std::copy(blocks.begin(), blocks.end(), mGameBlocks.begin());
}

void Ball::BeginPlay()
{
	SetBallStartShotDirection();
}

void Ball::Update()
{
	if (!HasShot)
	{
		SetEntityPosition(glm::vec2(mPlayer->GetEntityPosition()->x + 25, 500));
	}
	else
	{
		MoveBall(mBallMovementX,mBallMovementY);
		

		if (GetEntityPosition()->x <= 0)
		{
			mBallMovementX = 1;
		}

		if (GetEntityPosition()->x >= 770)
		{
			mBallMovementX = -1;
		}

		if (GetEntityPosition()->y <= 0)
		{
			mBallMovementY = 1;
		}

		if (GetEntityPosition()->y >= 570)
		{
			GameController::GameLives--;
			HasShot = false;
			SetBallStartShotDirection();
		}

		for (auto& block : mGameBlocks)
		{
			if (GetEntityTransform()->HasCollided(*block.GetEntityTransform()))
			{
				GameController::GameScore += 10;
				block.SetEntityPosition(glm::vec2(-100));
			}
		}
	}
}

void Ball::MoveBall(const int xDir, const int yDir)
{
	SetEntityPosition(glm::vec2(GetEntityPosition()->x + xDir, GetEntityPosition()->y + yDir));
}

void Ball::SetBallStartShotDirection()
{
	mFirstShotSwap = GHelper->GenerateRandomInt(0, 1);
	if (!mFirstShotSwap)
	{
		mBallMovementX = 1;
		mBallMovementY = -1;
	}
	else
	{
		mBallMovementX = -1;
		mBallMovementY = -1;
	}
}
