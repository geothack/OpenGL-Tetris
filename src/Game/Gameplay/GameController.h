#pragma once

#include "Gameplay/LivesText.h"
#include "Gameplay/Block.h"
#include "Gameplay/Ball.h"

class GameController : public Entity
{
public:
	GameController() = default;
	GameController(std::span<Block,30> blocks, Ball& ball);
	~GameController() override;

	void BeginPlay() override;
	void Update() override;

	inline static int GameLives = 3;
	inline static int GameScore = 0;
	inline static int GameLevel = 1;

private:
	void SetBlockPositions(const int amount);

private:

	enum class Level
	{
		NONE = -1,
		Lv1,
		Lv2,
		Lv3,
		Lv4,
		Lv5,
		Lv6,
		Lv7,
		Lv8,
		Lv9,
		Lv10,
	};

	Level mGameLevel = Level::Lv1;

	std::array<Block, 30> mGameBlocks;

	Ball* mBall;
};

