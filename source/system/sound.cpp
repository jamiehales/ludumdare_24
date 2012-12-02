#include <cstring>

#include "fmod.hpp"

#include "system/sound.h"

#if defined(PIXELBOOST_PLATFORM_NACL)
    #include "ppapi/cpp/instance.h"
    #include "ppapi/c/pp_instance.h"

    #include "ppapi/c/ppp_graphics_3d.h"
    #include "ppapi/lib/gl/gles2/gl2ext_ppapi.h"

    #include "fmodnacl.h"

    #include "game/game.h"
#endif

SoundSystem::SoundSystem()
{
    FMOD::System_Create(&_System);
    
#if defined(PIXELBOOST_PLATFORM_WINDOWS)
    _System->init(32, FMOD_INIT_NORMAL | FMOD_INIT_ENABLE_PROFILE, 0);
#elif defined(PIXELBOOST_PLATFORM_NACL)
    FMOD_NACL_EXTRADRIVERDATA extraDriverData;
    memset(&extraDriverData, 0, sizeof(FMOD_NACL_EXTRADRIVERDATA));
    extraDriverData.instance = static_cast<pp::Instance*>(Game::Instance()->GetViewController())->pp_instance();
        
    _System->init(32, FMOD_INIT_NORMAL, &extraDriverData);
#else
    FMOD_RESULT      result;
    int              numdrivers;
    FMOD_SPEAKERMODE speakermode;
    FMOD_CAPS        caps;
    char             name[256];

	result = _System->getNumDrivers(&numdrivers);

    if (numdrivers == 0)
    {
        result = _System->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
    }
    else
    {
        result = _System->getDriverCaps(0, &caps, 0, &speakermode);

        result = _System->setSpeakerMode(speakermode);       /* Set the user selected speaker mode. */

        if (caps & FMOD_CAPS_HARDWARE_EMULATED)             /* The user has the 'Acceleration' slider set to off!  This is really bad for latency!. */
        {                                                   /* You might want to warn the user about this. */
            result = _System->setDSPBufferSize(1024, 10);
        }

        result = _System->getDriverInfo(0, name, 256, 0);

        if (strstr(name, "SigmaTel"))   /* Sigmatel sound devices crackle for some reason if the format is PCM 16bit.  PCM floating point output seems to solve it. */
        {
            result = _System->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0,0, FMOD_DSP_RESAMPLER_LINEAR);
        }
    }

    result = _System->init(100, FMOD_INIT_NORMAL, 0);
    if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)         /* Ok, the speaker mode selected isn't supported by this soundcard.  Switch it back to stereo... */
    {
        result = _System->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
            
        result = _System->init(100, FMOD_INIT_NORMAL, 0);/* ... and re-init. */
    }
#endif
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

	if (!file)
		return;

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
	if (_Sounds.find(name) == _Sounds.end())
		return;

    FMOD::Sound* sound = _Sounds[name];
    FMOD::Channel* channel;
    
    _System->playSound(FMOD_CHANNEL_FREE, sound, true, &channel);
    channel->setPaused(false);
    channel->setVolume(volume);
}

void SoundSystem::PlayMusic(const std::string& name)
{
	if (_Sounds.find(name) == _Sounds.end())
		return;

    FMOD::Sound* sound = _Sounds[name];
    FMOD::Channel* channel;
    
    sound->setLoopCount(-1);
    sound->setMode(FMOD_LOOP_NORMAL);
    _System->playSound(FMOD_CHANNEL_FREE, sound, true, &channel);
    channel->setPaused(false);
}
