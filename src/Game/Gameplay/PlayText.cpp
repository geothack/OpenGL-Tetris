#include "Utility/PreLibrary.h"
#include "PlayText.h"

void PlayText::BeginPlay()
{
}

void PlayText::Update()
{
	//GetComponent<OpenGLText>()->Message = "Play";
}

void PlayText::SetTextColor(const glm::vec3& color)
{
	GetComponent<OpenGLText>()->TextAttribs.Color = color;
}

void PlayText::SetTextMessage(std::string_view message)
{
	GetComponent<OpenGLText>()->Message = message.data();
}
