#pragma once

#include "Gameplay/LivesText.h"
#include "Gameplay/Block.h"
#include "Gameplay/Ball.h"
#include "Gameplay/Player.h"
#include "Gameplay/LivesText.h"
#include "Gameplay/LevelText.h"
#include "Gameplay/ScoreText.h"
#include "Gameplay/PlayText.h"
#include "Gameplay/QuitText.h"

class GameController : public Entity
{
public:
	GameController() = default;
	GameController(std::span<Block,30> blocks, Ball& ball, Player& player, LivesText& lives
	, LevelText& level, ScoreText& score, std::span<Entity,2> endScreenTexts, PlayText& play, QuitText& quit
	, Window& window);
	~GameController() override;

	void BeginPlay() override;
	void Update() override;

	inline static int GameLives = 3;
	inline static int GameScore = 0;
	inline static int GameLevel = 1;

	void SetBlockPositions(const int amount);

	void ShakeScreen();

	bool Shake = false;

	void ResetEndScreenText();

private:

	std::array<Block, 30> mGameBlocks;

	std::array<Entity, 2> mEndScreenTexts;

	Window* mWindow;

	Ball* mBall;
	Player* mPlayer;

	LivesText* mLivesText;
	LevelText* mLevelText;
	ScoreText* mScoreText;
	PlayText* mPlayText;
	QuitText* mQuitText;

	int mPrevLevelScore = -1;

	int mCounter = 0;

	float mTimer = 0.0f;

	bool mQuitGame = false;
};

