#include "Utility/PreLibrary.h"
#include "GameController.h"

GameController::GameController(LivesText& livesText) : mLivesText(&livesText)
{
}

GameController::~GameController()
{
}

void GameController::BeginPlay()
{
}

void GameController::Update()
{
	mLivesText->GetComponent<OpenGLText>()->Message = "LIVES   " + std::to_string(GameLives);
}
