#pragma once

#include "pixelboost/framework/game.h"

namespace FMOD
{
    class Channel;
    class ChannelGroup;
    class DSP;
    class Sound;
    class System;
}

namespace pb
{
    class OrthographicCamera; 
    class RenderLayer;
    class Scene;
    class Viewport;
}

class World;

class Game : public pb::Game
{
public:
    Game(void* viewController);
    ~Game();
    
    virtual void Update(float time);
    virtual void Render();
    
private:
    pb::OrthographicCamera* _Camera;
    pb::Viewport* _Viewport;
    
    pb::RenderLayer* _Layer;
    
    World* _World;
    
    FMOD::ChannelGroup* _FmodGroup;
    FMOD::System* _FmodSystem;
    FMOD::DSP* _FmodDSP;
    FMOD::Channel* _FmodChannel;
    FMOD::Sound* _FmodSound;
};
