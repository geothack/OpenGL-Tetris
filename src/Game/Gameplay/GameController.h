#pragma once

#include "Gameplay/LivesText.h"
#include "Gameplay/Block.h"
#include "Gameplay/Ball.h"
#include "Gameplay/Player.h"

class GameController : public Entity
{
public:
	GameController() = default;
	GameController(std::span<Block,30> blocks, Ball& ball, Player& player);
	~GameController() override;

	void BeginPlay() override;
	void Update() override;

	inline static int GameLives = 3;
	inline static int GameScore = 0;
	inline static int GameLevel = 1;

	void SetBlockPositions(const int amount);

private:

	std::array<Block, 30> mGameBlocks;

	Ball* mBall;
	Player* mPlayer;

	int mPrevLevelScore = -1;
};

