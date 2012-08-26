#include "pixelboost/framework/screen.h"
#include "pixelboost/graphics/renderer/font/fontRenderer.h"
#include "pixelboost/graphics/renderer/sprite/spriteRenderer.h"

#include "game/game.h"
#include "screens/end.h"
#include "screens/game.h"
#include "screens/menu.h"
#include "system/sound.h"

Game::Game(void* viewController)
    : pb::Game(viewController)
    , _CurrentScreen(0)
{
    GetSpriteRenderer()->LoadSpriteSheet(pb::kFileLocationBundle, "game");
    GetFontRenderer()->LoadFont(pb::kFileLocationBundle, "earthman", "/data/fonts/earthman");
    
    _SoundSystem = new SoundSystem();
    
    _SoundSystem->LoadSound("hit_1", pb::kFileLocationBundle, "/data/audio/sfx/hit_1.wav");
    _SoundSystem->LoadSound("hit_2", pb::kFileLocationBundle, "/data/audio/sfx/hit_2.wav");
    _SoundSystem->LoadSound("hit_3", pb::kFileLocationBundle, "/data/audio/sfx/hit_3.wav");
    _SoundSystem->LoadSound("shoot_1", pb::kFileLocationBundle, "/data/audio/sfx/shoot_1.wav");
    _SoundSystem->LoadSound("shoot_2", pb::kFileLocationBundle, "/data/audio/sfx/shoot_2.wav");
    _SoundSystem->LoadSound("explosion_1", pb::kFileLocationBundle, "/data/audio/sfx/explosion_1.wav");
    _SoundSystem->LoadSound("explosion_2", pb::kFileLocationBundle, "/data/audio/sfx/explosion_2.wav");
    
    Transition(kGameModeMenu);
}

Game::~Game()
{

}

Game* Game::Instance()
{
    return static_cast<Game*>(pb::Game::Instance());
}

void Game::Update(float time)
{
    _SoundSystem->Update(time);
    _CurrentScreen->Update(time);
    
    pb::Game::Update(time);
}

void Game::Render()
{
    pb::Game::Render();
}

SoundSystem* Game::GetSoundSystem()
{
    return _SoundSystem;
}

void Game::Transition(GameMode mode, int params)
{
    if (_CurrentScreen)
    {
        _CurrentScreen->SetActive(false);
        delete _CurrentScreen;
    }
    
    switch (mode)
    {
        case kGameModeMenu:
            _CurrentScreen = new MenuScreen();
            break;
        case kGameModeGame:
            _CurrentScreen = new GameScreen(params);
            break;
        case kGameModeEnd:
            _CurrentScreen = new EndScreen(params);
            break;
    }
    
    _CurrentScreen->SetActive(true);
}
