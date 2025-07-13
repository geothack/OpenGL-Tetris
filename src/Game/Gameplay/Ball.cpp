#include "Utility/PreLibrary.h"
#include "Ball.h"
#include "Utility/ResourceCache.h"

Ball::Ball(Entity& player) : mPlayer(&player)
{
}

void Ball::BeginPlay()
{
}

void Ball::Update()
{
	if (!HasShot)
	{
		SetEntityPosition(glm::vec2(mPlayer->GetEntityPosition()->x + 25, GetEntityPosition()->y));
	}
	else
	{
		SwitchDirection(1, -1);
	}
}

void Ball::SwitchDirection(const int xDir, const int yDir)
{
	SetEntityPosition(glm::vec2(GetEntityPosition()->x + xDir, GetEntityPosition()->y + yDir));
}
