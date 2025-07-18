#include "Utility/PreLibrary.h"
#include "Player.h"
#include "Input/Input.h"
#include "Application.h"

Player::Player(Ball& ball, Window& window, TitleText& title, PlayText& play, QuitText& quit) : mBall(&ball), mWindow(&window)
	, mTitle(&title), mPlay(&play), mQuit(&quit)
{

}

void Player::BeginPlay()
{

}

void Player::Update()
{
	if (Application::GameState == GameState::GameStart)
	{
		if (GInput->KeyPressed("Escape"))
		{
			mWindow->SetWindowIsOpen(false);
		}

		if (GInput->KeyPressed("W"))
		{
			mPlay->SetTextColor(glm::vec3(0.75, 0.0, 0.75));
			mQuit->SetTextColor(glm::vec3(1.0));
			mQuitGame = false;
		}

		if (GInput->KeyPressed("S"))
		{
			mPlay->SetTextColor(glm::vec3(1.0));
			mQuit->SetTextColor(glm::vec3(0.75, 0.0, 0.75));
			mQuitGame = true;
		}
		if (GInput->KeyPressed("Return"))
		{
			Application::GameState = GameState::GameLoop;
			if (mQuitGame)
			{
				mWindow->SetWindowIsOpen(false);
			}

			//mTitle->AddComponent<int>(0.5);
			//mPlay->GetComponent<OpenGLText>()->TextAttribs.X = -500;
			//mQuit->SetTextMessage("");
			
		}
	}
	if (Application::GameState == GameState::GameLoop)
	{
		if (GInput->KeyPressed("A") && GetEntityPosition()->x > 0)
		{
			SetEntityPosition(glm::vec2(GetEntityPosition()->x - PlayerSpeed, GetEntityPosition()->y));
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

}
