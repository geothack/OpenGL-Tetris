#pragma once

#include "Gameplay/Ball.h"
#include "Gameplay/TitleText.h"
#include "Gameplay/PlayText.h"
#include "Gameplay/QuitText.h"

class Player : public Entity
{
public:
	Player() = default;
	Player(Ball& ball, Window& window, TitleText& title, PlayText& play, QuitText& quit);

	void BeginPlay() override;
	void Update() override;

	inline static int PlayerSpeed = 1;

private:
	Ball* mBall;
	Window* mWindow;

	TitleText* mTitle;
	PlayText* mPlay;
	QuitText* mQuit;

	bool mQuitGame = false;
};

