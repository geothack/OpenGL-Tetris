#include "Utility/PreLibrary.h"
#include "TitleText.h"

void TitleText::BeginPlay()
{
}

void TitleText::Update()
{
	//GetComponent<OpenGLText>()->Message = "Breakout";
}

void TitleText::SetTextMessage(std::string_view message)
{
	GetComponent<OpenGLText>()->Message = message.data();
}

void TitleText::SetTextColor(const glm::vec3& color)
{
	GetComponent<OpenGLText>()->TextAttribs.Color = color;
}
