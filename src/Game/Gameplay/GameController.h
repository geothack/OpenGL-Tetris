#pragma once

#include "Gameplay/LivesText.h"

class GameController : public Entity
{
public:
	GameController() = default;
	~GameController() override;

	void BeginPlay() override;
	void Update() override;

	inline static int GameLives = 3;
	inline static int GameScore = 0;

private:
};

