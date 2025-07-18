#include "Utility/PreLibrary.h"
#include "Player.h"
#include "Input/Input.h"
#include "Application.h"
#include "Gameplay/GameController.h"


Player::Player(Ball& ball, Window& window, TitleText& title, PlayText& play, QuitText& quit, GameController& controller
	,LivesText& lives, LevelText& level, ScoreText& score) : mBall(&ball), mWindow(&window)
	, mTitle(&title), mPlay(&play), mQuit(&quit), mController(&controller), mLivesText(&lives), mLevelText(&level)
	, mScoreText(&score)
{

}

void Player::BeginPlay()
{

}

void Player::Update()
{
	if (GInput->KeyPressed("Escape"))
	{
		mWindow->SetWindowIsOpen(false);
	}
	if (Application::GameState == GameState::GameStart)
	{
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

			mTitle->SetTextColor(glm::vec3(0.0));
			mTitle->GetComponent<OpenGLText>()->TextAttribs.X = -2000;
			mPlay->SetTextColor(glm::vec3(0.0));
			mPlay->GetComponent<OpenGLText>()->TextAttribs.X = -2000;
			mQuit->SetTextColor(glm::vec3(0.0));
			mQuit->GetComponent<OpenGLText>()->TextAttribs.X = -2000;
			SetEntityPosition(glm::vec2(340,550));
			mController->SetBlockPositions(10);
			mLivesText->SetTextColor(glm::vec3(1.0));
			mLevelText->SetTextColor(glm::vec3(1.0));
			mScoreText->SetTextColor(glm::vec3(1.0));

			//mBall->GetComponent<OpenGLShader>()->SetFloat("Alpha", 1.0);
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
