#pragma once

#include <map>
#include <string>

#include "pixelboost/file/fileSystem.h"
#include "pixelboost/logic/system.h"

namespace FMOD
{
    class Channel;
    class ChannelGroup;
    class DSP;
    class Sound;
    class System;
}

class SoundSystem
{
public:
    SoundSystem();
    ~SoundSystem();
    
    void Update(float time);
    
    void LoadSound(const std::string& name, pb::FileLocation fileLocation, const std::string& filename);
    void PlaySound(const std::string& name, float pitch, float volume);
    
private:
    FMOD::System* _System;
    std::map<std::string, FMOD::Sound*> _Sounds;
};
