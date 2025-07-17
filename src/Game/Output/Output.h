#pragma once

#include "Output/Sound.h"

class Output
{
public:
	static Output* Get();

	void Init();
	void LoadSound(std::string_view name, const std::filesystem::path& filePath);
	void ALPlaySound(std::string_view name);
	void StopSound(std::string_view name);

	void Free();

private:
	inline static Output* mOutput = nullptr;

	Sound mSoundEffects;
};