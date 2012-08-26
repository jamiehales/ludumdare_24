#include "pixelboost/file/fileSystem.h"
#include "pixelboost/graphics/camera/camera.h"
#include "pixelboost/graphics/camera/viewport.h"
#include "pixelboost/graphics/device/device.h"
#include "pixelboost/graphics/renderer/common/renderer.h"
#include "pixelboost/graphics/renderer/font/fontRenderer.h"
#include "pixelboost/graphics/renderer/sprite/spriteRenderer.h"
#include "pixelboost/logic/component/graphics/rectangle.h"
#include "pixelboost/logic/entity.h"
#include "pixelboost/logic/scene.h"

#include "game/game.h"
#include "game/world.h"
#include "system/sound.h"

Game::Game(void* viewController)
    : pb::Game(viewController)
{
    _Camera = new pb::OrthographicCamera();
    
    _Viewport = new pb::Viewport(0, _Camera);
    
    GetSpriteRenderer()->LoadSpriteSheet(pb::kFileLocationBundle, "game");
    GetFontRenderer()->LoadFont(pb::kFileLocationBundle, "earthman", "/data/fonts/earthman");
    
    _SoundSystem = new SoundSystem();
    _World = new World();
    _Viewport->SetScene(_World);
    
    _SoundSystem->LoadSound("hit_1", pb::kFileLocationBundle, "/data/audio/sfx/hit_1.wav");
    _SoundSystem->LoadSound("hit_2", pb::kFileLocationBundle, "/data/audio/sfx/hit_2.wav");
    _SoundSystem->LoadSound("hit_3", pb::kFileLocationBundle, "/data/audio/sfx/hit_3.wav");
    _SoundSystem->LoadSound("shoot_1", pb::kFileLocationBundle, "/data/audio/sfx/shoot_1.wav");
    _SoundSystem->LoadSound("shoot_2", pb::kFileLocationBundle, "/data/audio/sfx/shoot_2.wav");
    _SoundSystem->LoadSound("explosion_1", pb::kFileLocationBundle, "/data/audio/sfx/explosion_1.wav");
    _SoundSystem->LoadSound("explosion_2", pb::kFileLocationBundle, "/data/audio/sfx/explosion_2.wav");
    
    pb::Renderer::Instance()->AddViewport(_Viewport);
}

Game::~Game()
{
    pb::Renderer::Instance()->RemoveViewport(_Viewport);
    
    delete _Viewport;
    delete _Camera;
}

Game* Game::Instance()
{
    return static_cast<Game*>(pb::Game::Instance());
}

void Game::Update(float time)
{
    _SoundSystem->Update(time);
    _World->Update(time);
    
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
