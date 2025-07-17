#include "Utility\PreLibrary.h"
#include "ZSound.h"

ZSound::ZSound()
{

}

ZSound::~ZSound()
{
    Cleanup();
    if (mContext)
    {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(mContext);
    }
    if (mDevice)
    {
        alcCloseDevice(mDevice);
    }
}

void ZSound::Init()
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

void ZSound::LoadSound(std::string_view name, const std::filesystem::path& filePath)
{
    auto path = filePath.string();

    SF_INFO sfInfo;
    SNDFILE* sndFile = sf_open(path.c_str(), SFM_READ, &sfInfo);
    if (!sndFile)
    {
        throw std::runtime_error("Failed to load sound file: " + path);
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
        throw std::runtime_error("Failed to indentify file format");
    }


    // Read audio data
    std::vector<short> samples(sfInfo.frames * sfInfo.channels);
    sf_count_t numFrames = sf_readf_short(sndFile, samples.data(), sfInfo.frames);
    sf_close(sndFile);

    if (numFrames < 1)
    {
        throw std::runtime_error("Failed to read audio data from file: " + path);
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

void ZSound::ALPlaySound(std::string_view name)
{
    auto it = soundMap.find(name.data());
    auto string = static_cast<std::string>(name);
    if (it == soundMap.end())
    {
        throw std::runtime_error("Sound not found: " + string);
    }
    alSourcePlay(it->second.Source);
    CheckOpenALError("Failed to play sound");
}

void ZSound::StopSound(std::string_view name)
{
    auto it = soundMap.find(name.data());
    auto string = static_cast<std::string>(name);
    if (it == soundMap.end())
    {
        throw std::runtime_error("Sound not found: " + string);
    }
    alSourceStop(it->second.Source);
    CheckOpenALError("Failed to stop sound");
}

void ZSound::Cleanup()
{
    for (auto& pair : soundMap)
    {
        alDeleteSources(1, &pair.second.Source);
        alDeleteBuffers(1, &pair.second.Buffer);
    }
    soundMap.clear();
}

void ZSound::CheckOpenALError(std::string_view message)
{
    ALenum error = alGetError();
    auto string = static_cast<std::string>(message);

    if (error != AL_NO_ERROR)
    {
        throw std::runtime_error(string + " (OpenAL error: " + std::to_string(error) + ")");
    }
}

