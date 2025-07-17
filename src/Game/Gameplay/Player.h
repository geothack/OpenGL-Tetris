#pragma once

#include "Gameplay/Ball.h"

class Player : public Entity
{
public:
	Player() = default;
	Player(Ball& ball, Window& window, std::span<Entity,3> texts);

	void BeginPlay() override;
	void Update() override;

	inline static int PlayerSpeed = 1;

private:
	Ball* mBall;
	Window* mWindow;

	std::array<Entity, 3> mStartScreenTexts;

	bool mQuitGame = false;
};

