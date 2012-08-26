#pragma once

#include "pixelboost/framework/game.h"

class SoundSystem;

class Game : public pb::Game
{
public:
    Game(void* viewController);
    ~Game();
    
    static Game* Instance();
    
    virtual void Update(float time);
    virtual void Render();
    
    SoundSystem* GetSoundSystem();
    
    enum GameMode
    {
        kGameModeMenu,
        kGameModeGame,
        kGameModeEnd,
    };
    
    void Transition(GameMode mode, int params = 0);
    
private:
    pb::Screen* _CurrentScreen;
    SoundSystem* _SoundSystem;
};
