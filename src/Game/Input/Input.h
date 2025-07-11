#pragma once

#include "Input/Keyboard.h"

class Input
{
public:
	static Input* Get();

	void UpdateKeys();

	bool KeyPressed(std::string_view keyName);

	void Free();

private:
	inline static Input* mInput = nullptr;

	::Keyboard mKeyboard;
};

