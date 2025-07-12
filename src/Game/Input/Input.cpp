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

bool Input::KeyPressedDown(std::string_view keyName)
{
	return mKeyboard.KeyPressedDown(keyName);
}

bool Input::KeyPressedUp(std::string_view keyName)
{
	return mKeyboard.KeyPressedUp(keyName);
}

void Input::Free()
{
	delete mInput;
}
