#include "Utility/PreLibrary.h"
#include "ScoreText.h"
#include "Gameplay/GameController.h"

ScoreText::~ScoreText()
{
}

void ScoreText::BeginPlay()
{
}

void ScoreText::Update()
{
	GetComponent<OpenGLText>()->Message = "SCORE   " + std::to_string(GameController::GameScore);
}
