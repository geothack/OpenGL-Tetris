#pragma once

#include "Gameplay/Block.h"

class Ball : public Entity
{
public:
	Ball() = default;

	Ball(Entity& player, std::span<Block> blocks);

	void BeginPlay() override;
	void Update() override;

	bool HasShot = false;

private:
	void MoveBall(const int xDir, const int yDir);

	void SetBallStartShotDirection();

private:
	Entity* mPlayer;

	bool mFirstShotSwap = false;

	int mBallMovementX = 0;
	int mBallMovementY = 0;

	std::array<Block, 30> mGameBlocks;
};

