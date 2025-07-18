#include "Utility/PreLibrary.h"
#include "QuitText.h"

void QuitText::BeginPlay()
{
}

void QuitText::Update()
{
	//GetComponent<OpenGLText>()->Message = "Quit";
}

void QuitText::SetTextColor(const glm::vec3& color)
{
	GetComponent<OpenGLText>()->TextAttribs.Color = color;
}

void QuitText::SetTextMessage(std::string_view message)
{
	GetComponent<OpenGLText>()->Message = message.data();
}
