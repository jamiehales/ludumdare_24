#include "pixelboost/file/fileSystem.h"
#include "pixelboost/graphics/camera/camera.h"
#include "pixelboost/graphics/camera/viewport.h"
#include "pixelboost/graphics/device/device.h"
#include "pixelboost/graphics/renderer/common/renderer.h"
#include "pixelboost/graphics/renderer/sprite/spriteRenderer.h"
#include "pixelboost/logic/component/graphics/rectangle.h"
#include "pixelboost/logic/entity.h"
#include "pixelboost/logic/scene.h"

#include "game/game.h"
#include "game/world.h"

#include "fmod.hpp"

Game::Game(void* viewController)
    : pb::Game(viewController)
{
    _Camera = new pb::OrthographicCamera();
    
    _Viewport = new pb::Viewport(0, _Camera);
    
    GetSpriteRenderer()->LoadSpriteSheet(pb::kFileLocationBundle, "game");
    
    _World = new World();
    _Viewport->SetScene(_World->GetScene());
    
    pb::Renderer::Instance()->AddViewport(_Viewport);
    
    /*
    FMOD::System_Create(&_FmodSystem);

    _FmodSystem->init(32, FMOD_INIT_NORMAL | FMOD_INIT_ENABLE_PROFILE, NULL);
    
    pb::File* file = pb::FileSystem::Instance()->OpenFile(pb::kFileLocationBundle, "/data/audio/sfx/ting.wav");
    std::vector<unsigned char> data;
    file->ReadAll(data);
    delete file;
    
    FMOD_RESULT result;
    
    FMOD_CREATESOUNDEXINFO info;
    memset(&info, 0, sizeof(FMOD_CREATESOUNDEXINFO));
    info.length = data.size();
    info.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
    result = _FmodSystem->createSound((char*)(&data[0]), FMOD_SOFTWARE|FMOD_OPENMEMORY, &info, &_FmodSound);
    
    _FmodSystem->createChannelGroup("noises", &_FmodGroup);
    
    result = _FmodSystem->playSound(FMOD_CHANNEL_FREE, _FmodSound, true, &_FmodChannel);
    _FmodSystem->playSound(FMOD_CHANNEL_FREE, _FmodSound, true, &_FmodChannel);
    _FmodChannel->setPaused(false);
     */
}

Game::~Game()
{
    pb::Renderer::Instance()->RemoveViewport(_Viewport);
    
    delete _Viewport;
    delete _Camera;
}

void Game::Update(float time)
{
    _World->Update(time);
    
    /*
    static int count = 0;
    count++;
    
    if (count % 5 == 0)
    {
        count = 0;
        
        FMOD_RESULT result;
        result = _FmodSystem->playSound(FMOD_CHANNEL_FREE, _FmodSound, true, &_FmodChannel);
        _FmodChannel->setChannelGroup(_FmodGroup);
        _FmodGroup->setPitch((float)rand()/(float)RAND_MAX);
        
        _FmodChannel->setPaused(false);
    }
    
    if (_FmodSystem != NULL)
    {
        _FmodSystem->update();
    }
    */

    pb::Game::Update(time);
}

void Game::Render()
{
    pb::Game::Render();
}
