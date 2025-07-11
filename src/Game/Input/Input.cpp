#include "Utility/PreLibrary.h"
#include "Input.h"

Input* Input::Get()
{
	if (!mInput)
	{
		mInput = new Input();
	}

	return mInput;
}

void Input::UpdateKeys()
{
	mKeyboard.Update();
}

bool Input::KeyPressed(std::string_view keyName)
{
	return mKeyboard.KeyPressed(keyName);
}

void Input::Free()
{
	delete mInput;
}
