#pragma once

#include "pixelboost/framework/game.h"

namespace pb
{
    class OrthographicCamera; 
    class RenderLayer;
    class Scene;
    class Viewport;
}

class SoundSystem;
class World;

class Game : public pb::Game
{
public:
    Game(void* viewController);
    ~Game();
    
    static Game* Instance();
    
    virtual void Update(float time);
    virtual void Render();
    
    SoundSystem* GetSoundSystem();
    
private:
    pb::OrthographicCamera* _Camera;
    pb::Viewport* _Viewport;
    
    pb::RenderLayer* _Layer;
    
    World* _World;
    
    SoundSystem* _SoundSystem;
};
