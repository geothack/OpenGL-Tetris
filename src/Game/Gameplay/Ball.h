#pragma once

#include "Gameplay/Block.h"

class Ball : public Entity
{
public:
	Ball() = default;

	Ball(Entity& player, std::span<Block,30> blocks);

	void BeginPlay() override;
	void Update() override;

	void SetBallStartShotDirection();

	bool HasShot = false;

	inline static int BallTimeStep = 3;

private:
	void MoveBall(const int xDir, const int yDir);

private:
	Entity* mPlayer;

	bool mFirstShotSwap = false;

	int mBallMovementX = 0;
	int mBallMovementY = 0;

	int mStepMovement = 0;

	std::array<Block, 30> mGameBlocks;
};

