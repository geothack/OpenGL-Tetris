#include "Utility/PreLibrary.h"
#include "GameController.h"
#include "Utility/ResourceCache.h"
#include "Render/OpenGLTexture.h"
#include "Render/OpenGLShader.h"
#include "Application.h"
#include "Input/Input.h"

GameController::GameController(std::span<Block, 30> blocks, Ball& ball, Player& player, LivesText& lives
	, LevelText& level, ScoreText& score, std::span<Entity, 2> endScreenTexts, PlayText& play, QuitText& quit
, Window& window) : mBall(&ball), mPlayer(&player), mLivesText(&lives), mLevelText(&level)
	, mScoreText(&score), mPlayText(&play), mQuitText(&quit), mWindow(&window)
{
	if (blocks.size() != 30)
	{
		Verify::Update("Span must have exactly 30 elements.", 0);
	}
	std::copy(blocks.begin(), blocks.end(), mGameBlocks.begin());

	if (endScreenTexts.size() != 2)
	{
		Verify::Update("Span must have exactly 2 elements.", 0);
	}
	std::copy(endScreenTexts.begin(), endScreenTexts.end(), mEndScreenTexts.begin());
}

GameController::~GameController()
{
}

void GameController::BeginPlay()
{

	//SetBlockPositions(10);
	
}

void GameController::Update()
{
	if (Shake)
	{
		ShakeScreen();

		if (mCounter % 30 == 0)
		{
			mTimer += 0.025f;
		}

		if (mTimer >= 2)
		{
			mCounter = 0;
			mTimer = 0.0f;
			Shake = false;
		}
	}


	// Lv2
	if (GameScore == 100)
	{
		SetBlockPositions(20);
		GameScore += 10;
		GameLevel++;
		mBall->HasShot = false;
		mBall->SetBallStartShotDirection();
		if (GameLevel % 2 == 0)
		{
			GameLives++;
		}
	}
	// Lv3
	if (GameScore == 310)
	{
		SetBlockPositions(30);
		GameScore += 10;
		GameLevel++;
		mBall->HasShot = false;
		mBall->SetBallStartShotDirection();
	}
	// Lv4
	if (GameScore == 620)
	{
		SetBlockPositions(30);
		GameScore += 10;
		GameLevel++;
		mBall->HasShot = false;
		mBall->SetBallStartShotDirection();
		mBall->BallTimeStep--;
		if (GameLevel % 2 == 0)
		{
			GameLives++;
		}
	}
	// Lv5
	if (GameScore == 930)
	{
		SetBlockPositions(30);
		GameScore += 10;
		GameLevel++;
		mBall->HasShot = false;
		mBall->SetBallStartShotDirection();
		mPlayer->SetEntitySize(glm::vec2(80, 20));
		Player::PlayerSpeed = 2;
		//Ball::BallTimeStep--;
		mPrevLevelScore = GameScore;
	}
	// Lv6 -- Infinite Loop Mechanic 
	if (GameScore == mPrevLevelScore + 300)
	{
		if (GameLevel % 2 == 0)
		{
			GameLives++;
		}

		SetBlockPositions(30);
		GameScore += 10;
		GameLevel++;
		mBall->HasShot = false;
		mBall->SetBallStartShotDirection();
		mPrevLevelScore = GameScore;
	}

	
	if (GameLives <= -1)
	{
		Application::GameState = GameState::GameEnd;
		for (auto i = 0; i < 30; i++)
		{
			mGameBlocks[i].SetEntityPosition(glm::vec2(-500, -500));
		}
		mPlayer->SetEntityPosition(glm::vec2(-500, 550));
		mLivesText->SetTextColor(glm::vec3(0.0));
		mLevelText->SetTextColor(glm::vec3(0.0));
		mScoreText->SetTextColor(glm::vec3(0.0));

		mEndScreenTexts[0].GetComponent<OpenGLText>()->TextAttribs.Color = glm::vec3(0.75, 0.0, 0.75);
		mEndScreenTexts[0].GetComponent<OpenGLText>()->TextAttribs.X = 160;
		mEndScreenTexts[1].GetComponent<OpenGLText>()->TextAttribs.X = 160;
		mEndScreenTexts[1].GetComponent<OpenGLText>()->Message = "Levels | " + std::to_string(GameLevel) + "                  Score | "
			+ std::to_string(GameScore);

		mPlayText->SetTextColor(glm::vec3(0.75,0.0,0.75));
		mPlayText->GetComponent<OpenGLText>()->TextAttribs.X = 350;
		mQuitText->SetTextColor(glm::vec3(1.0));
		mQuitText->GetComponent<OpenGLText>()->TextAttribs.X = 350;
		GameLives = 3;
	}
}

void GameController::SetBlockPositions(const int amount)
{
	auto xPos = 10;
	auto yPos = -40;
	for (auto i = 0; i < amount; i++)
	{
		if (i % 10 == 0)
		{
			xPos = 10;
			yPos += 50;
		}
		mGameBlocks[i].GetComponent<Transform>()->UpdatePosition(glm::vec2(xPos, yPos));
		xPos += 80;
	}
}

void GameController::ShakeScreen()
{
	mCounter += 2;
	Cache->Find<OpenGLShader>("ShakeScreen")->Attach();
	Cache->Find<OpenGLShader>("ShakeScreen")->SetFloat("time", mTimer);
}

void GameController::ResetEndScreenText()
{
	mEndScreenTexts[0].GetComponent<OpenGLText>()->TextAttribs.X = -1000;
	mEndScreenTexts[1].GetComponent<OpenGLText>()->TextAttribs.X = -1000;
}
