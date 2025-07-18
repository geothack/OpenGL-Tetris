#pragma once

#include "Gameplay/Ball.h"
#include "Gameplay/TitleText.h"
#include "Gameplay/PlayText.h"
#include "Gameplay/QuitText.h"
#include "Gameplay/LivesText.h"
#include "Gameplay/LevelText.h"
#include "Gameplay/ScoreText.h"


class GameController;

class Player : public Entity
{
public:
	Player() = default;
	Player(Ball& ball, Window& window, TitleText& title, PlayText& play, QuitText& quit, GameController& controller
	, LivesText& lives, LevelText& level, ScoreText& score);

	void BeginPlay() override;
	void Update() override;

	inline static int PlayerSpeed = 1;

private:
	Ball* mBall;
	GameController* mController;
	Window* mWindow;

	TitleText* mTitle;
	PlayText* mPlay;
	QuitText* mQuit;

	LivesText* mLivesText;
	LevelText* mLevelText;
	ScoreText* mScoreText;

	bool mQuitGame = false;
};

