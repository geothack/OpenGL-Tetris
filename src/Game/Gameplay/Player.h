#pragma once

#include "Gameplay/Ball.h"

class Player : public Entity
{
public:
	Player() = default;
	Player(Ball& ball);

	void BeginPlay() override;
	void Update() override;

	inline static int PlayerSpeed = 1;

private:
	Ball* mBall;
};

