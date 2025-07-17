#include "Utility\PreLibrary.h"
#include "Sound.h"
#include "Utility/Verify.h"

Sound::Sound()
{

}

Sound::~Sound()
{
    /*Cleanup();
    if (mContext)
    {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(mContext);
    }
    if (mDevice)
    {
        alcCloseDevice(mDevice);
    }*/
}

void Sound::Init()
{
    // Initialize OpenAL
    mDevice = alcOpenDevice(nullptr);
    if (!mDevice)
    {
        throw std::runtime_error("Failed to open OpenAL device");
    }

    mContext = alcCreateContext(mDevice, nullptr);
    if (!mContext || !alcMakeContextCurrent(mContext))
    {
        throw std::runtime_error("Failed to create or set OpenAL context");
    }
}

void Sound::LoadSound(std::string_view name, const std::filesystem::path& filePath)
{
    auto path = filePath.string();

    SF_INFO sfInfo;
    SNDFILE* sndFile = sf_open(path.c_str(), SFM_READ, &sfInfo);
    if (!sndFile)
    {
        Verify::Update("Failed to load sound file: " + path, 0);
    }

    ALenum format;
    if (sfInfo.channels == 1)
    {
        format = AL_FORMAT_MONO16;
    }
    else if (sfInfo.channels == 2)
    {
        format = AL_FORMAT_STEREO16;
    }
    else
    {
        std::println("Unsupported channel count| {}", sfInfo.channels);
        sf_close(sndFile);
        Verify::Update("Failed to indentify file format", 0);
    }


    // Read audio data
    std::vector<short> samples(sfInfo.frames * sfInfo.channels);
    sf_count_t numFrames = sf_readf_short(sndFile, samples.data(), sfInfo.frames);
    sf_close(sndFile);

    if (numFrames < 1)
    {
        Verify::Update("Failed to read audio data from file| " + path, 0);
    }

    // Create OpenAL buffer and source
    ALuint buffer;
    ALuint source;
    alGenBuffers(1, &buffer);
    CheckOpenALError("Failed to generate OpenAL buffer");
    alBufferData(buffer, format, samples.data(), samples.size() * sizeof(short), sfInfo.samplerate);
    CheckOpenALError("Failed to buffer audio data");

    alGenSources(1, &source);
    CheckOpenALError("Failed to generate OpenAL source");
    alSourcei(source, AL_BUFFER, buffer);

    // Store in map
    soundMap[name.data()] = {buffer, source};
}

void Sound::ALPlaySound(std::string_view name)
{
    auto it = soundMap.find(name.data());
    auto string = static_cast<std::string>(name);
    if (it == soundMap.end())
    {
        Verify::Update("Sound not found| " + string, 0);
    }
    alSourcePlay(it->second.Source);
    CheckOpenALError("Failed to play sound");
}

void Sound::StopSound(std::string_view name)
{
    auto it = soundMap.find(name.data());
    auto string = static_cast<std::string>(name);
    if (it == soundMap.end())
    {
        Verify::Update("Sound not found: " + string, 0);
    }
    alSourceStop(it->second.Source);
    CheckOpenALError("Failed to stop sound");
}

void Sound::Free()
{
    for (auto& pair : soundMap)
    {
        alDeleteSources(1, &pair.second.Source);
        alDeleteBuffers(1, &pair.second.Buffer);
    }
    soundMap.clear();
}

void Sound::CheckOpenALError(std::string_view message)
{
    ALenum error = alGetError();
    auto string = static_cast<std::string>(message);

    if (error != AL_NO_ERROR)
    {
        Verify::Update(string + " (OpenAL error: " + std::to_string(error) + ")", 0);
    }
}

