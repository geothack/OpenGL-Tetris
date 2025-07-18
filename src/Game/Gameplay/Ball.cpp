#include "Utility/PreLibrary.h"
#include "Ball.h"
#include "Utility/ResourceCache.h"
#include "Utility/Helper.h"
#include "Gameplay/GameController.h"
#include "Utility/Verify.h"
#include "Output/Output.h"

Ball::Ball(Entity& player, std::span<Block, 30> blocks, GameController& controller) : mPlayer(&player), mController(&controller)
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
		SetEntityPosition(glm::vec2(mPlayer->GetEntityPosition()->x + mPlayer->GetEntitySize()->x / 2 - GetEntitySize()->x / 2, 500));
	}
	else
	{
		mStepMovement++;
		if (mStepMovement % BallTimeStep == 0)
		{
			MoveBall(mBallMovementX, mBallMovementY);
		}
		

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
			GOutput->ALPlaySound("LostLife");
			mController->Shake = true;
		}

		if (GetEntityPosition()->y >= mPlayer->GetEntityPosition()->y - 22
			&& GetEntityPosition()->y <= mPlayer->GetEntityPosition()->y + 2
			&& GetEntityPosition()->x + 15 >= mPlayer->GetEntityPosition()->x 
			&& GetEntityPosition()->x + 15 <= mPlayer->GetEntityPosition()->x + mPlayer->GetEntitySize()->x)
		{
			mBallMovementY = -1;
		}

		for (auto& block : mGameBlocks)
		{
			if (GetEntityTransform()->HasCollided(*block.GetEntityTransform()))
			{
				GameController::GameScore += 10;
				block.SetEntityPosition(glm::vec2(-100));
				mBallMovementY == 1 ? mBallMovementY = -1 : mBallMovementY = 1;
				GOutput->ALPlaySound("Hit");
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
