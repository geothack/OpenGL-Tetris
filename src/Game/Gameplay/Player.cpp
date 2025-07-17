#include "Utility/PreLibrary.h"
#include "Player.h"
#include "Input/Input.h"
#include "Application.h"

Player::Player(Ball& ball, Window& window, std::span<Entity,3> texts) : mBall(&ball), mWindow(&window)
{
	if (texts.size() != 3)
	{
		Verify::Update("Span must have exactly 3 elements.", 0);
	}
	std::copy(texts.begin(), texts.end(), mStartScreenTexts.begin());
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
			mStartScreenTexts[1].GetComponent<OpenGLText>()->TextAttribs.Color = glm::vec3(0.75, 0.0, 0.75);
			mStartScreenTexts[2].GetComponent<OpenGLText>()->TextAttribs.Color = glm::vec3(1.0);
			mQuitGame = false;
		}

		if (GInput->KeyPressed("S"))
		{
			mStartScreenTexts[1].GetComponent<OpenGLText>()->TextAttribs.Color = glm::vec3(1.0);
			mStartScreenTexts[2].GetComponent<OpenGLText>()->TextAttribs.Color = glm::vec3(0.75, 0.0, 0.75);
			mQuitGame = true;
		}
		if (GInput->KeyPressed("Return"))
		{
			Application::GameState = GameState::GameLoop;
			if (mQuitGame)
			{
				mWindow->SetWindowIsOpen(false);
			}

			for (auto i = 0; i < 3; i++)
			{
				//mStartScreenTexts[i].GetComponent<OpenGLText>()->Message.X = -500;
			}
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
