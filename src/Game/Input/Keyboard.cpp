#include "Utility/PreLibrary.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{
    int numKeys;
    const auto* state = SDL_GetKeyboardState(&numKeys);
    for (int i = 0; i < numKeys; ++i)
    {
        mKeyCache[SDL_GetScancodeName(static_cast<SDL_Scancode>(i))] = state[i];
    }
}

void Keyboard::Update()
{
    const auto* state = SDL_GetKeyboardState(nullptr);
    for (auto& keyState : mKeyCache)
    {
        SDL_Scancode scancode = SDL_GetScancodeFromName(keyState.first.c_str());
        if (scancode != SDL_SCANCODE_UNKNOWN)
        {
            keyState.second = state[scancode];
        }
    }
}

bool Keyboard::KeyPressed(std::string_view keyName)
{
    SDL_Scancode scancode = SDL_GetScancodeFromName(keyName.data());
    if (scancode == SDL_SCANCODE_UNKNOWN)
    {
        std::println("Invalid key name {}", keyName);
        return false;
    }
    return mKeyCache[keyName.data()] == 1;
}
