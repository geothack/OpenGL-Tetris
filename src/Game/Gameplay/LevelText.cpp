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

void LevelText::SetTextColor(const glm::vec3& color)
{
	GetComponent<OpenGLText>()->TextAttribs.Color = color;
}
