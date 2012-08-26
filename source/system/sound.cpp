#include "fmod.hpp"

#include "system/sound.h"

SoundSystem::SoundSystem()
{
    FMOD::System_Create(&_System);
    
    _System->init(32, FMOD_INIT_NORMAL | FMOD_INIT_ENABLE_PROFILE, NULL);
}

SoundSystem::~SoundSystem()
{
    
}

void SoundSystem::Update(float time)
{
    _System->update();
}

void SoundSystem::LoadSound(const std::string& name, pb::FileLocation fileLocation, const std::string& filename)
{
    FMOD_RESULT result;
    
    pb::File* file = pb::FileSystem::Instance()->OpenFile(fileLocation, filename);
    std::vector<unsigned char> data;
    file->ReadAll(data);
    delete file;
    
    FMOD::Sound* sound;
    
    FMOD_CREATESOUNDEXINFO info;
    memset(&info, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    info.length = (unsigned int)data.size();
    info.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    result = _System->createSound((char*)(&data[0]), FMOD_SOFTWARE|FMOD_OPENMEMORY, &info, &sound);
    
    _Sounds[name] = sound;
}

void SoundSystem::PlaySound(const std::string& name, float pitch, float volume)
{
    FMOD::Sound* sound = _Sounds[name];
    FMOD::Channel* channel;
    
    _System->playSound(FMOD_CHANNEL_FREE, sound, true, &channel);
    channel->setPaused(false);
    channel->setVolume(volume);
}
