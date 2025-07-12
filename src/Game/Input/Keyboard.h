#pragma once


class Keyboard
{
public:
    Keyboard();
        
    void Update();
        
    bool KeyPressed(std::string_view keyName);
        
    bool KeyPressedDown(std::string_view keyName);

    bool KeyPressedUp(std::string_view keyName);
      

private:
    std::vector<Uint8> mCurrentState;
    std::vector<Uint8> mPreviousState;
};

