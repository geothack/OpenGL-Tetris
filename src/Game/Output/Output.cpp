#include "Utility/PreLibrary.h"
#include "Output.h"

Output* Output::Get()
{
	if (!mOutput)
	{
		mOutput = new Output();
	}

	return mOutput;
}

void Output::Init()
{
	mSoundEffects.Init();
}

void Output::LoadSound(std::string_view name, const std::filesystem::path& filePath)
{
	mSoundEffects.LoadSound(name, filePath);
}

void Output::ALPlaySound(std::string_view name)
{
	mSoundEffects.ALPlaySound(name);
}

void Output::StopSound(std::string_view name)
{
	mSoundEffects.StopSound(name);
}

void Output::Free()
{
	mSoundEffects.Free();
	delete mOutput;
}
