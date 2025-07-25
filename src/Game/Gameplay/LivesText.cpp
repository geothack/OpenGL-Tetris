#include "Utility/PreLibrary.h"
#include "LivesText.h"
#include "Gameplay/GameController.h"

void LivesText::BeginPlay()
{
}

void LivesText::Update()
{
	GetComponent<OpenGLText>()->Message = "LIVES  " + std::to_string(GameController::GameLives);
}

void LivesText::SetTextColor(const glm::vec3& color)
{
	GetComponent<OpenGLText>()->TextAttribs.Color = color;
}
