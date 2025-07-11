#pragma once


class Keyboard
{
public:
	Keyboard();

    void Update();
        
    bool KeyPressed(std::string_view keyName);
        
private:
	std::unordered_map<std::string, Uint8> mKeyCache;
};

