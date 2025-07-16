#include "Utility/PreLibrary.h"
#include "LevelText.h"
#include "Gameplay/GameController.h"

LevelText::~LevelText()
{
}

void LevelText::BeginPlay()
{
}

void LevelText::Update()
{
	GetComponent<OpenGLText>()->Message = "LEVEL  " + std::to_string(GameController::GameLevel);
}
