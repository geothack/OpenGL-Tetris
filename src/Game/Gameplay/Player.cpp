#include "Utility/PreLibrary.h"
#include "Player.h"
#include "Input/Input.h"

Player::Player()
{
}

void Player::BeginPlay()
{

}

void Player::Update()
{
	if (GInput->KeyPressedDown("A") && GetEntityPosition()->x > 0)
	{
		SetEntityPosition(glm::vec2(GetEntityPosition()->x - 1,GetEntityPosition()->y));
	}

	if (GInput->KeyPressedDown("D") && GetEntityPosition()->x < 720)
	{
		SetEntityPosition(glm::vec2(GetEntityPosition()->x + 1, GetEntityPosition()->y));
	}

}
