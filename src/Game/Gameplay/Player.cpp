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
	if (GInput->KeyPressedDown("A"))
	{
		SetEntityPosition(glm::vec2(GetEntityPosition()->x - 1,GetEntityPosition()->y));
	}

	if (GInput->KeyPressedDown("D"))
	{
		SetEntityPosition(glm::vec2(GetEntityPosition()->x + 1, GetEntityPosition()->y));
	}

	if (GInput->KeyPressedDown("W"))
	{
		SetEntityPosition(glm::vec2(GetEntityPosition()->x, GetEntityPosition()->y - 1));
	}

	if (GInput->KeyPressedDown("S"))
	{
		SetEntityPosition(glm::vec2(GetEntityPosition()->x, GetEntityPosition()->y + 1));
	}

}
