#include "Utility/PreLibrary.h"
#include "Player.h"
#include "Input/Input.h"

Player::Player(Ball& ball) : mBall(&ball)
{
}

void Player::BeginPlay()
{

}

void Player::Update()
{
	if (GInput->KeyPressed("A") && GetEntityPosition()->x > 0)
	{
		SetEntityPosition(glm::vec2(GetEntityPosition()->x - PlayerSpeed,GetEntityPosition()->y));
	}

	if (GInput->KeyPressed("D") && GetEntityPosition()->x < 800 - GetEntitySize()->x)
	{
		SetEntityPosition(glm::vec2(GetEntityPosition()->x + PlayerSpeed, GetEntityPosition()->y));
	}

	if (GInput->KeyPressedDown("Space") && !GInput->KeyPressedUp("Space") && !mBall->HasShot)
	{
		mBall->HasShot = true;
	}

}
