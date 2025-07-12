#include "Utility/PreLibrary.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{
    int numKeys;
    SDL_GetKeyboardState(&numKeys);
    mCurrentState.resize(numKeys);
    mPreviousState.resize(numKeys);
}

void Keyboard::Update()
{
    mPreviousState = mCurrentState;

    const auto* state = SDL_GetKeyboardState(nullptr);
    memcpy(mCurrentState.data(), state, mCurrentState.size());
}

bool Keyboard::KeyPressed(std::string_view keyName)
{
    SDL_Scancode scancode = SDL_GetScancodeFromName(keyName.data());
    return scancode != SDL_SCANCODE_UNKNOWN && mCurrentState[scancode];
}

bool Keyboard::KeyPressedDown(std::string_view keyName)
{
    SDL_Scancode scancode = SDL_GetScancodeFromName(keyName.data());
    return scancode != SDL_SCANCODE_UNKNOWN &&
        mCurrentState[scancode] && !mPreviousState[scancode];
}

bool Keyboard::KeyPressedUp(std::string_view keyName)
{
    SDL_Scancode scancode = SDL_GetScancodeFromName(keyName.data());
    return scancode != SDL_SCANCODE_UNKNOWN &&
        !mCurrentState[scancode] && mPreviousState[scancode];
}
