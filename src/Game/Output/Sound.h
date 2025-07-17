#pragma once


class Sound
{
public:
    Sound();
    ~Sound();

    void Init();
    void LoadSound(std::string_view name, const std::filesystem::path& filePath);
    void ALPlaySound(std::string_view name);
    void StopSound(std::string_view name);
    void Free();

private:
    struct SoundData
    {
        ALuint Buffer;
        ALuint Source;
    };

    std::map<std::string, SoundData> soundMap;

    void CheckOpenALError(std::string_view message);

    ALCdevice* mDevice;
    ALCcontext* mContext;
};

